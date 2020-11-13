// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpookyScuffleCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"	
#include "Animation/AnimTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "../LDBlock/CheckPoint.h"
#include "../LDBlock/AreaDamage.h"
#include "../LDBlock/TPPoint.h"


ASpookyScuffleCharacter::ASpookyScuffleCharacter()
	: ATwoHandedSwordCharacter{}
{
	saveType = 0;
	sensibilityX = 5.f;
	sensibilityZ = 5.f;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f;
	cameraBoom->bUsePawnControlRotation = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

}

void ASpookyScuffleCharacter::BeginPlay()
{
	Super::BeginPlay();

	saveTimerBLL = timerBatLostLife;
	saveTimerDL = timerDrainLife;
	saveMaxAngleLock = angleLock;
	saveTimerSecuritySP = timerSecuritySP;
	saveTimerPressBF = timerPressBatForm;
}

void ASpookyScuffleCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ASpookyScuffleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);


	PlayerInputComponent->BindAction("Lock", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateLock);
	PlayerInputComponent->BindAction("Lock", IE_Released, this, &ASpookyScuffleCharacter::DisableLock);

	if (playerCanJump)
	{
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
		PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &ASpookyScuffleCharacter::SetBatMode);
		PlayerInputComponent->BindAction("RightTrigger", IE_Released, this, &ASpookyScuffleCharacter::UnSetBatMode);
	}
	else
	{
		PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &ASpookyScuffleCharacter::SetBatMode);
		PlayerInputComponent->BindAction("RightTrigger", IE_Released, this, &ASpookyScuffleCharacter::UnSetBatMode);
	}
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASpookyScuffleCharacter::Attack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateDash);
	PlayerInputComponent->BindAction("Special", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateSpecialAttack);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpookyScuffleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpookyScuffleCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpookyScuffleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpookyScuffleCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Next", IE_Pressed, this, &ASpookyScuffleCharacter::NextTPPoint);
	PlayerInputComponent->BindAction("Prev", IE_Pressed, this, &ASpookyScuffleCharacter::PrevTPPoint);
	PlayerInputComponent->BindAction("CurrentTP", IE_Pressed, this, &ASpookyScuffleCharacter::CurrentTPPoint);
	
}

void ASpookyScuffleCharacter::TurnAtRate(float _rate)
{
	if (!loadLock)
	{
		if (invertXAxis)
			AddControllerYawInput(_rate * sensibilityX * -10 * GetWorld()->GetDeltaSeconds());
		else
			AddControllerYawInput(_rate * sensibilityX * 10 * GetWorld()->GetDeltaSeconds());

		if (!loadLock && blockCameraPitch && !unlockPitch)
		{
			FRotator _newRot = GetController()->GetControlRotation();

			if (_newRot.Pitch > 180)
			{
				if (_newRot.Pitch < axisCam)
					_newRot.Pitch += speedRotCam * GetWorld()->DeltaTimeSeconds;
				if (_newRot.Pitch > axisCam)
					_newRot.Pitch -= speedRotCam * GetWorld()->DeltaTimeSeconds;
			}
			else
			{
				if (_newRot.Pitch < axisCam - 360)
					_newRot.Pitch += speedRotCam * GetWorld()->DeltaTimeSeconds;
				if (_newRot.Pitch > axisCam - 360)
					_newRot.Pitch -= speedRotCam * GetWorld()->DeltaTimeSeconds;
			}
			
			GetController()->SetControlRotation(_newRot);
		}
	}
}

void ASpookyScuffleCharacter::LookUpAtRate(float _rate)
{
	if (!loadLock)
	{
		if (!blockCameraPitch)
			AddControllerPitchInput(_rate * sensibilityZ * GetWorld()->GetDeltaSeconds());
		else
		{
			if (_rate == 0)
				unlockPitch = false;
			else
				unlockPitch = true;

			if (unlockPitch)
			{
				FRotator _newRot = GetController()->GetControlRotation();

				if (_newRot.Pitch > 180)
				{
					if (_newRot.Pitch > axisCam + limitPitch)
						_rate = 0;
					if (_newRot.Pitch < axisCam - limitPitch)
						_rate = 0;
				}
				else
				{
					if (_newRot.Pitch > (axisCam - 360) + limitPitch)
						_rate = 0;
					if (_newRot.Pitch < (axisCam - 360) - limitPitch)
						_rate = 0;
				}


				if (_rate != 0)
				{
					if (invertZAxis)
						AddControllerPitchInput(_rate * sensibilityZ * -10 * GetWorld()->GetDeltaSeconds());
					else
						AddControllerPitchInput(_rate * sensibilityZ * 10 * GetWorld()->GetDeltaSeconds());
				}
			}
		}
	}
}

void ASpookyScuffleCharacter::MoveForward(float _value)
{
	if (playerMovable)
	{
		Super::MoveForward(_value);
	}
}

void ASpookyScuffleCharacter::MoveRight(float _value)
{
	if (playerMovable)
	{
		Super::MoveRight(_value);
	}
}

void ASpookyScuffleCharacter::ModifyLife(int _lifePoint, E_TEAMS _team, bool _stun)
{
	Super::ModifyLife(_lifePoint, _team, _stun);
}

void ASpookyScuffleCharacter::Attack()
{
	if (!isBatMode && playerMovable)
	{
		Super::Attack();

		if (drainBlood)
			stopDrain = true;
	}
}

// =============================================== Dash ===============================================//

void ASpookyScuffleCharacter::ActivateDash()
{
	if (playerMovable)
	{
		if (drainBlood)
			stopDrain = true;

		if (!isDash && !isBatMode && !drainBlood)
		{
			isAttacking = false;
			canAttack = false;
			isDash = true;
			savePosDash = GetActorLocation();
			isSlowDash = true;
			GetWorldTimerManager().SetTimer(outHandleDash, this, &ASpookyScuffleCharacter::DashMovement, GetWorld()->GetDeltaSeconds(), true);
		}
	}
}

void ASpookyScuffleCharacter::DashMovement()
{
	if (!isCoolDownDash)
	{
		// Movement Of Dash
		timerDash += GetWorld()->DeltaTimeSeconds;
		
		if ((savePosDash - GetActorLocation()).Size() < distanceDash)
		{
			canAttack = false;
			GetCharacterMovement()->Velocity = GetActorForwardVector() * speedDash * 10;
			GetCharacterMovement()->MaxAcceleration = speedDash * 10;
		}
		if (timerDash > distanceDash / 1000.f || (savePosDash - GetActorLocation()).Size() >= distanceDash)
		{
			isCoolDownDash = true;
			timerDash = 0;
			canAttack = true;
			GetCharacterMovement()->MaxAcceleration = 2048; // default value 
			GetCharacterMovement()->Velocity = GetActorForwardVector() * 0;
			GetCharacterMovement()->MaxWalkSpeed -= slowSpeed;
			FTimerHandle _timeHandle;
			GetWorldTimerManager().SetTimer(_timeHandle, this, &ASpookyScuffleCharacter::ResetDashSpeed, slowTime, false);

		}
	}
	else
	{
		// CoolDown Of Dash
		timerCoolDownDash += GetWorld()->DeltaTimeSeconds;

		if (timerCoolDownDash > coolDownDash)
		{
			isCoolDownDash = false;
			timerCoolDownDash = 0.f;
			isDash = false;
			GetWorldTimerManager().ClearTimer(outHandleDash);
		}
	}
}

void ASpookyScuffleCharacter::DashCD()
{

}

void ASpookyScuffleCharacter::ResetDashSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed += slowSpeed;
	isSlowDash = false;
}

// =============================================== Lock =============================================== //

void ASpookyScuffleCharacter::ActivateLock()
{
	if (!loadLock)
	{
		loadLock = true;
		passToDisable = false;

		angleLock = saveMaxAngleLock;

		TArray<AActor*> enemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneralCharacter::StaticClass(), enemies);

		APlayerCameraManager* _camera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		FVector _forwardVec = { _camera->GetActorForwardVector().X,_camera->GetActorForwardVector().Y, 0 };

		for (AActor* enemOfList : enemies)
		{
			AGeneralCharacter* enemy = Cast<AGeneralCharacter>(enemOfList);

			if (enemy != nullptr && enemy != this && enemy->IsAlive())
			{
				
				if (CheckEnemyToLock(enemy->GetActorLocation(),_camera->GetCameraLocation(), _forwardVec))
					enemyToLock = enemy;
			}
		}

		if (cameraBoom != nullptr)
			saveArmLength = this->cameraBoom->TargetArmLength;

		if (enemyToLock != nullptr)
		{
			SoundEnterLock();
			enemyToLock->isLock = true;
			enemyToLock->TargetEvent();
			GetWorldTimerManager().SetTimer(outHandleLock, this, &ASpookyScuffleCharacter::LockEnemy, GetWorld()->GetDeltaSeconds(), true);
		}
	}
}

// verify angle and take the lower 
bool ASpookyScuffleCharacter::CheckEnemyToLock(FVector enemy, FVector posPlayer , FVector forwardVec)
{
		if ((enemy - posPlayer).Size() < distanceMaxLock)
		{
			//FVector _forwardVec = { GetActorForwardVector().X,GetActorForwardVector().Y, 0};
			FVector _playerToEnemy = { (enemy - posPlayer).X, (enemy - posPlayer).Y, 0 };

			float  _calcAngle = FVector::DotProduct(forwardVec.GetSafeNormal(), _playerToEnemy.GetSafeNormal());
			float _newAngle = (acosf(_calcAngle)) * 180 / PI;

			if (_newAngle < angleLock)
			{
				angleLock = _newAngle;
				return true;
			}
		}
		else
		{
			return false;
		}

		return false;
}

// Camera lock change of place
void ASpookyScuffleCharacter::LockEnemy()
{
	LockPosition(enemyToLock->GetActorLocation(),true);

	if (passToDisable)
	{
		GetWorldTimerManager().ClearTimer(outHandleLock);
	}
}

void ASpookyScuffleCharacter::LockPosition(FVector pos, bool moveCam)
{
	loadLock = true;

	FVector  _camTransform = followCamera->GetRelativeLocation();
	FVector _dirPlayerEnemy = { GetActorLocation().X - pos.X, GetActorLocation().Y - pos.Y,0 };

	// == Camera focus on the enemy lock calcul 
	float _nice = 100;

	if ((GetActorLocation() - pos).Size() < limitUpCamera)
	{
		_nice = _nice * ((GetActorLocation() - pos).Size() / limitUpCamera);
	}

	FRotator _newRot;
	FVector _currentPos = GetActorLocation() + FVector(0, 0, _nice);
	FVector _targetPos = pos - FVector(0, 0, _nice);

	FRotator _lookAt = FRotationMatrix::MakeFromX(_targetPos - _currentPos).Rotator();
	FRotator _terp = UKismetMathLibrary::RInterpTo(GetController()->GetControlRotation(), _lookAt, GetWorld()->DeltaTimeSeconds, 5.f);

	_newRot.Roll = GetController()->GetControlRotation().Roll;
	_newRot.Pitch = _terp.Pitch;
	_newRot.Yaw = _terp.Yaw;

	GetController()->SetControlRotation(_newRot);
	
	if (moveCam)
	{
		// Move Camera to the good Angle when you lock 
		if (cameraBoom->TargetArmLength > 400)
			cameraBoom->TargetArmLength -= speedCameraLock * GetWorld()->DeltaTimeSeconds;

		if (_camTransform.Y < 230 && _camTransform.Z < 70)
		{
			_camTransform.Z += speedCameraLock * GetWorld()->DeltaTimeSeconds;
			_camTransform.Y += speedCameraLock * GetWorld()->DeltaTimeSeconds;
			followCamera->SetRelativeLocation(_camTransform);
		}
	}
}


// ===================== disable lock 

void ASpookyScuffleCharacter::DisableLock()
{
	GetWorldTimerManager().SetTimer(outHandleExitLock, this, &ASpookyScuffleCharacter::ExitLock, GetWorld()->GetDeltaSeconds(), true);

	passToDisable = true;
}

// Reset value 
void ASpookyScuffleCharacter::ExitLock()
{
	FVector  _camTransform = followCamera->GetRelativeLocation();
	float _multiplReset = 4;

	if (ExitLockCondition())
	{
		if (enemyToLock != nullptr)
		{
			SoundExitLock();
			enemyToLock->isLock = false;
			enemyToLock->TargetEvent();
			enemyToLock = nullptr;
		}

		loadLock = false;
		
		GetWorldTimerManager().ClearTimer(outHandleExitLock);
	}
}

bool ASpookyScuffleCharacter::ExitLockCondition()
{
	FVector  _camTransform = followCamera->GetRelativeLocation();
	float _multiplReset = 10;

	bool _firstCondition = false, _scndCondition = false;

	if (saveArmLength > cameraBoom->TargetArmLength)
	{
		cameraBoom->TargetArmLength += speedCameraLock * _multiplReset * GetWorld()->DeltaTimeSeconds;
	}
	else
	{
		cameraBoom->TargetArmLength = saveArmLength;
		_firstCondition = true;
	}

	if (_camTransform.Y > 0 && _camTransform.Z > 0)
	{
		_camTransform.Z -= speedCameraLock * _multiplReset * GetWorld()->DeltaTimeSeconds;
		_camTransform.Y -= speedCameraLock * _multiplReset * GetWorld()->DeltaTimeSeconds;
		followCamera->SetRelativeLocation(_camTransform);
	}
	else
	{
		followCamera->SetRelativeLocation({ 0,0,0 });
		_scndCondition = true;
	}

	if (_firstCondition && _scndCondition)
	{
		loadLock = false;
		return true;
	}

	return false;
}
// =============================================== Event Sound Lock ===============================================//

void ASpookyScuffleCharacter::SoundEnterLock_Implementation()
{
}
void ASpookyScuffleCharacter::SoundExitLock_Implementation()
{
}

// =============================================== Bat Form ===============================================//

void ASpookyScuffleCharacter::SetBatMode()
{
	if (isSlowDash || isAttacking)
		return;

	if ((playerMovable && !drainBlood) )
	{
		if (!isBatMode && pressIsOk)
		{ 
			canAttack = false;
			SoundEnterBat();
			isBatMode = true;
			BatEvent();
			ModifyLife(-costTransformToBat, E_TEAMS::Enemy, false);
			//life -= costTransformToBat;
			if (life <= 0)
				GameOverEvent();
			timerBatLostLife = saveTimerBLL;
			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * mutiplySpeedBatMode;
			GetWorldTimerManager().SetTimer(outHandleBatForm, this, &ASpookyScuffleCharacter::tickLostLifeBatForm, GetWorld()->GetDeltaSeconds(), true);
		}
	}
}

void ASpookyScuffleCharacter::UnSetBatMode()
{
	if (isSlowDash || isAttacking)
		return;

	if ((playerMovable && !drainBlood))
	{
		if (isBatMode)
		{
			pressIsOk = false;
			SoundExitBat();
			isBatMode = false;
			canAttack = true;
			BatEvent();
			GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
			//pressIsOk = true;
			GetWorldTimerManager().SetTimer(pressBat, this, &ASpookyScuffleCharacter::TimerTouchPressBat, GetWorld()->GetDeltaSeconds(), true);
		}
	}
}

void ASpookyScuffleCharacter::tickLostLifeBatForm()
{
	timerBatLostLife -= GetWorld()->DeltaTimeSeconds;

	if (timerBatLostLife <= 0)
	{

		ModifyLife(-costBatForm * countBat, E_TEAMS::Enemy, false);
		//life -= costBatForm;
		if (life <= 0)
			GameOverEvent();
		timerBatLostLife = saveTimerBLL;

		if (otherExpo)
			countBat += countBat;
		else
			countBat++;
	}

	if (!isBatMode)
	{
		GetWorldTimerManager().ClearTimer(outHandleBatForm);
		countBat = 1;
	}
}

void ASpookyScuffleCharacter::TimerTouchPressBat()
{
	timerPressBatForm -= GetWorld()->DeltaTimeSeconds;

	if (timerPressBatForm <= 0)
	{
		pressIsOk = true;
		GetWorldTimerManager().ClearTimer(pressBat);
		timerPressBatForm = saveTimerPressBF;
	}
}

void ASpookyScuffleCharacter::BatEvent_Implementation()
{

}

// =============================================== Sound Event Bat ===============================================//

void ASpookyScuffleCharacter::SoundEnterBat_Implementation()
{
}

void ASpookyScuffleCharacter::SoundExitBat_Implementation()
{
}

// =============================================== Special Attack ===============================================//

void ASpookyScuffleCharacter::ActivateSpecialAttack()
{
	if (enemyToLock != nullptr)
	{
		useIsDrain = true;
		drainBlood = false;
	}

	if (useIsDrain && enemyToLock != nullptr)
	{
		enemyToEat = enemyToLock;
		timerSecuritySP = saveTimerSecuritySP;
		GetWorldTimerManager().SetTimer(outHandleSpecialAttack, this, &ASpookyScuffleCharacter::SpecialAttackMove, 
									GetWorld()->GetDeltaSeconds(), true);
	}
}

void ASpookyScuffleCharacter::SpecialAttackMove()
{
	
	FVector _dirVec = enemyToEat->GetActorLocation() - GetActorLocation();
	FVector _posBehindEnemy = enemyToEat->GetActorLocation() - (enemyToEat->GetActorForwardVector() * 100);

	enemyToEat->SetCanAttack(false);

	if (_dirVec.Size() < 150)
		enemyToEat->stun = true;

	if (_dirVec.Size() < distanceMaxToDrain && !drainBlood)
	{
		FRotator rotPlayer = FRotationMatrix::MakeFromX(FVector(_dirVec)).Rotator();
		rotPlayer.Pitch = GetActorRotation().Pitch;
		// rotate the player
		SetActorRotation(rotPlayer);

		// go to back of enemy quickly
		if ((_posBehindEnemy - GetActorLocation()).Size() >= 60) // bug if you change too much the scale of enemy because the forwardvector up his position
		{
			GetCharacterMovement()->Velocity = (_posBehindEnemy - GetActorLocation()).GetSafeNormal()
				* speedSpecialAttack * mutiplySpeedSpecialAttack;

			// Security if player is block by object on scene
			timerSecuritySP -= GetWorld()->DeltaTimeSeconds;
			if (timerSecuritySP <= 0)
			{
				ResetDrainValue();
				GetWorldTimerManager().ClearTimer(outHandleSpecialAttack);
				return;
			}
		}
		else
		{
			GetCharacterMovement()->Velocity = { 0,0,0 };
			if (isBatMode)
				UnSetBatMode();

			drainBlood = true;
			enemyToEat->stun = true;
			SoundEat();
			enemyToEat->ModifyLife(-GetDamage(), GetTeam(), false);
			saveLifePLayerOnDrain = life;	
		}
	}

	if (_dirVec.Size() > distanceMaxToDrain && !drainBlood)
	{
		useIsDrain = false;
		drainBlood = false;
		GetWorldTimerManager().ClearTimer(outHandleSpecialAttack);
	}

	if (drainBlood)
	{
		SpecialAttackDrain();
	}
}

void ASpookyScuffleCharacter::SpecialAttackDrain()
{
	timerDrainLife -= GetWorld()->DeltaTimeSeconds;

	if (timerDrainLife <= 0)
	{
		timerDrainLife = saveTimerDL;

		if (life < maxLife)
		{
			life += drainHowManyLife;
			saveLifePLayerOnDrain = life;
		}

		SoundDrain();
		enemyToEat->stun = true;
		enemyToEat->ModifyLife(-GetDamage(), GetTeam(), false);
	}

	if (!enemyToEat->IsAlive())
	{
		ResetDrainValue();
		GetWorldTimerManager().ClearTimer(outHandleSpecialAttack);
		return;
	}

	if (!(GetCharacterMovement()->Velocity).IsNearlyZero())
	{
		ResetDrainValue();
		GetWorldTimerManager().ClearTimer(outHandleSpecialAttack);
		return;
	}

	if (stopDrain)
	{
		stopDrain = false;
		ResetDrainValue();
		GetWorldTimerManager().ClearTimer(outHandleSpecialAttack);
		return;
	}

	if (stun)
	{
		ResetDrainValue();
		GetWorldTimerManager().ClearTimer(outHandleSpecialAttack);
		return;
	}
}

void ASpookyScuffleCharacter::ResetDrainValue()
{
	enemyToEat->SetCanAttack(true);
	drainBlood = false;
	useIsDrain = false;
	enemyToEat->stun = false;
	enemyToEat = nullptr;
}
// =============================================== / Sound Special Attack / ===============================================//
void ASpookyScuffleCharacter::SoundEat_Implementation()
{

}
void ASpookyScuffleCharacter::SoundDrain_Implementation()
{

}

// =============================================== / Events / ===============================================//

void ASpookyScuffleCharacter::GameOverEvent_Implementation()
{
	if (isBatMode)
		UnSetBatMode();

	playerMovable = false;
}

void ASpookyScuffleCharacter::YouWinEvent_Implementation()
{
	if (isBatMode)
		UnSetBatMode();

	youWin = true;

	playerMovable = false;
}

void ASpookyScuffleCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<UAreaDamage>(OtherComp))
	{
		areaDamage = Cast<UAreaDamage>(OtherComp);

		if (areaDamage->team != GetTeam())
		{
			this->ModifyLife(-areaDamage->damageTaken, areaDamage->team, false);
			GetWorldTimerManager().SetTimer(timerHandle, this, &AGeneralCharacter::TakeDamageByArea, GetWorld()->GetDeltaSeconds(), true);
		}
	}

	if (Cast<ACheckPoint>(OtherActor))
	{

		ACheckPoint* _checkPoint = Cast<ACheckPoint>(OtherActor);

		if (myCheckPoint == nullptr)
			myCheckPoint = _checkPoint;

		if (!_checkPoint->IsCheck())
		{
			_checkPoint->CheckIsOk();

			if (_checkPoint->orderCheckPoint > myCheckPoint->orderCheckPoint)
				myCheckPoint = _checkPoint;
		}
	}
}

// =============================================== / Debug / ===============================================//

void ASpookyScuffleCharacter::PrevTPPoint()
{
	TpPoint(-1);
}

void ASpookyScuffleCharacter::NextTPPoint()
{
	TpPoint(1);
}

void ASpookyScuffleCharacter::CurrentTPPoint()
{
	TpPoint(0);
}

void ASpookyScuffleCharacter::TpPoint(int move)
{
	TArray<AActor*> _tPPoint;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATPPoint::StaticClass(), _tPPoint);
	bool check = false;

	for (AActor* _pointOfTp : _tPPoint)
	{
		ATPPoint* _point = Cast<ATPPoint>(_pointOfTp);

		if (_point != nullptr && !check)
		{
			if (tPPointnumber + move == _point->pointNumber)
			{
				check = true;
				tPPointnumber = _point->pointNumber;
				SetActorLocation(_point->GetActorLocation());
			}
		}
	}
}

