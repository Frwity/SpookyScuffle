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


ASpookyScuffleCharacter::ASpookyScuffleCharacter()
	: ATwoHandedSwordCharacter{}
{
	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

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
}

void ASpookyScuffleCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ASpookyScuffleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASpookyScuffleCharacter::Attack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateDash);
	PlayerInputComponent->BindAction("Lock", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateLock);
	PlayerInputComponent->BindAction("Lock", IE_Released, this, &ASpookyScuffleCharacter::DisableLock); 
	PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &ASpookyScuffleCharacter::SetBatMode);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpookyScuffleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpookyScuffleCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpookyScuffleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpookyScuffleCharacter::LookUpAtRate);
	
}

void ASpookyScuffleCharacter::TurnAtRate(float _rate)
{
	AddControllerYawInput(_rate * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASpookyScuffleCharacter::LookUpAtRate(float _rate)
{
	AddControllerPitchInput(_rate * baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASpookyScuffleCharacter::MoveForward(float _value)
{
	Super::MoveForward(_value);
}

void ASpookyScuffleCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void ASpookyScuffleCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	Super::ModifyLife(_lifePoint, _team);
}

void ASpookyScuffleCharacter::Attack()
{
	if(!isBatMode)
		Super::Attack();
}

// =============================================== Dash ===============================================//

void ASpookyScuffleCharacter::ActivateDash()
{
	if (!isDash && !isBatMode)
	{
		isDash = true;
		savePosDash = GetActorLocation();
		GetWorldTimerManager().SetTimer(outHandleDash, this, &ASpookyScuffleCharacter::DashMovement, GetWorld()->GetDeltaSeconds(), true);
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
			GetCharacterMovement()->Velocity = GetActorForwardVector() * speedDash * 10;
			GetCharacterMovement()->MaxAcceleration = speedDash * 10;
		}
		if (timerDash > distanceDash / 1000.f || (savePosDash - GetActorLocation()).Size() >= distanceDash)
		{
			isCoolDownDash = true;
			timerDash = 0;
			GetCharacterMovement()->MaxAcceleration = 2048; // default value 
			GetCharacterMovement()->Velocity = GetActorForwardVector() * 0;
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

// =============================================== Lock =============================================== //

void ASpookyScuffleCharacter::ActivateLock()
{
	if (!loadLock)
	{
		loadLock = true;
		passToDisable = false;

		TArray<AActor*> enemiesTwoHanded;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATwoHandedSwordCharacter::StaticClass(), enemiesTwoHanded);

		angleLock = 60;

		for (AActor* enemOfList : enemiesTwoHanded)
		{
			ATwoHandedSwordCharacter* enemy = Cast<ATwoHandedSwordCharacter>(enemOfList);

			if (enemy != nullptr && enemy != this)
			{
				
				if (CheckEnemyToLock(enemy->GetActorLocation(), GetActorLocation()))
					enemyToLock = enemy;
			
			}
		}

		if (cameraBoom != nullptr)
			saveArmLength = this->cameraBoom->TargetArmLength;

		if (enemyToLock != nullptr)
		{
			GetWorldTimerManager().SetTimer(outHandleLock, this, &ASpookyScuffleCharacter::LockEnemy, GetWorld()->GetDeltaSeconds(), true);
			enemyToLock->Jump();
		}
	}
}

// verify angle and take the lower 
bool ASpookyScuffleCharacter::CheckEnemyToLock(FVector enemy, FVector posPlayer)
{
		if ((enemy - posPlayer).Size() < distanceMaxLock)
		{
			FVector _forwardVec = { GetActorForwardVector().X,GetActorForwardVector().Y, 0};
			FVector _playerToEnemy = { (enemy - posPlayer).X, (enemy - posPlayer).Y, 0 };

			float  _calcAngle = FVector::DotProduct(_forwardVec.GetSafeNormal(), _playerToEnemy.GetSafeNormal());
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

void myLerp(FRotator targetPos, FRotator currentPos)
{

}

// Camera lock change of place
void ASpookyScuffleCharacter::LockEnemy()
{
	FVector  _camTransform =  followCamera->GetRelativeLocation();
	FVector _dirPlayerEnemy = { GetActorLocation().X - enemyToLock->GetActorLocation().X,
						GetActorLocation().Y - enemyToLock->GetActorLocation().Y,0 };

	// == Camera focus on the enemy lock calcul 
	FRotator _newRot;
	FVector _currentPos = GetActorLocation() + FVector(0, 0, 100);
	FVector _targetPos = enemyToLock->GetActorLocation() - FVector(0,0,100);
	
	FRotator _lookAt = FRotationMatrix::MakeFromX(_targetPos - _currentPos).Rotator();
	FRotator _terp = UKismetMathLibrary::RInterpTo(GetController()->GetControlRotation(),_lookAt,GetWorld()->DeltaTimeSeconds,5.f);

	_newRot.Roll = GetController()->GetControlRotation().Roll;
	_newRot.Pitch = _terp.Pitch ;
	_newRot.Yaw = _terp.Yaw;

	GetController()->SetControlRotation(_newRot);

	//rotation player to enemy, needed to straff : Don't Work like I want

	//FRotator _terpPlayer = UKismetMathLibrary::RInterpTo(GetController()->GetControlRotation(), 
	//	FRotationMatrix::MakeFromX(-_dirPlayerEnemy).Rotator(), GetWorld()->DeltaTimeSeconds, 5.f);
	//SetActorRotation(_terpPlayer);
	
	// Move Camera to the good Angle when you lock 
	if (cameraBoom->TargetArmLength > 300)
		cameraBoom->TargetArmLength -= speedCameraLock * GetWorld()->DeltaTimeSeconds;
	
	if (_camTransform.Y < 100 && _camTransform.Z < 100)
	{
		_camTransform.Z += speedCameraLock * GetWorld()->DeltaTimeSeconds;
		_camTransform.Y += speedCameraLock * GetWorld()->DeltaTimeSeconds;
		followCamera->SetRelativeLocation(_camTransform);
	}

	if (passToDisable)
	{
		GetWorldTimerManager().ClearTimer(outHandleLock);
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

	bool _firstCondition = false, _scndCondition = false;



	if (saveArmLength > cameraBoom->TargetArmLength)
	{
		cameraBoom->TargetArmLength += speedCameraLock * 4 * GetWorld()->DeltaTimeSeconds;
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
		if (enemyToLock != nullptr)
		{
			enemyToLock->StopJumping();
			enemyToLock = nullptr;
		}

		loadLock = false;
		
		GetWorldTimerManager().ClearTimer(outHandleExitLock);
	}
}

// =============================================== Bat Form ===============================================//

void ASpookyScuffleCharacter::SetBatMode()
{
	isBatMode = !isBatMode;
	BatEvent();

	if (isBatMode)
	{
		life -= costTransformToBat;
		if (life <= 0)
			GameOverEvent();
		timerBatLostLife = saveTimerBLL;
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * mutiplySpeedBatMode;
		GetWorldTimerManager().SetTimer(outHandleBatForm, this, &ASpookyScuffleCharacter::tickLostLifeBatForm, GetWorld()->GetDeltaSeconds(), true);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / mutiplySpeedBatMode;
	}
}

void ASpookyScuffleCharacter::tickLostLifeBatForm()
{
	timerBatLostLife -= GetWorld()->DeltaTimeSeconds;

	if (timerBatLostLife <= 0)
	{
		life -= costBatForm;
		if (life <= 0)
			GameOverEvent();
		timerBatLostLife = saveTimerBLL;
	}

	if (!isBatMode)
	{
		GetWorldTimerManager().ClearTimer(outHandleBatForm);
	}

}

void ASpookyScuffleCharacter::BatEvent_Implementation()
{

}