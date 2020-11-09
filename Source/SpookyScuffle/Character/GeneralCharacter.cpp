// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralCharacter.h"
#include "TimerManager.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"	
#include "Animation/AnimTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "../LDBlock/AreaDamage.h"
#include "../LDBlock/DoorEnemy.h"


AGeneralCharacter::AGeneralCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.6f;
	life = maxLife;

}

void AGeneralCharacter::BeginPlay()
{
	Super::BeginPlay();

	life = maxLife;
	isAlive = true;
	
	walkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	rotationRate = GetCharacterMovement()->RotationRate;

	if (myDoor != nullptr)
		myDoor->SetGoalToUnlock();

	areaDamage = nullptr,

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGeneralCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AGeneralCharacter::OnOverlapEnd);

}

void AGeneralCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (invulnerabilityCD >= 0)
		invulnerabilityCD -= _deltaTime;
}

void AGeneralCharacter::MoveForward(float _value)
{
	if (stun)
		return;
	if ((Controller != NULL) && (_value != 0.0f))
	{	
		// find out which way is forward
		const FRotator _rotation = Controller->GetControlRotation();
		const FRotator _yawRotation(0, _rotation.Yaw, 0);

		// get forward vector
		const FVector _direction = FRotationMatrix(_yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(_direction, _value);	
	}
}

void AGeneralCharacter::MoveRight(float _value)
{
	if (stun)
		return;
	if ((Controller != NULL) && (_value != 0.0f))
	{
		// find out which way is right
		const FRotator _rotation = Controller->GetControlRotation();
		const FRotator _yawRotation(0, _rotation.Yaw, 0);

		// get right vector 
		const FVector _direction = FRotationMatrix(_yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(_direction, _value);	
	}
}

void AGeneralCharacter::ModifyLife(int _lifePoint, E_TEAMS _team, bool _stun)
{
	if (invulnerabilityCD >= 0 || !isAlive)
		return;

	if (_lifePoint < 0 && team != _team)
	{
		invulnerabilityCD = invulnerabilityTime;
		life += _lifePoint;

		if (_stun)
		{
			stun = true;
			if (isHit)
			{
				isHit = false;
				GetWorldTimerManager().ClearTimer(outHandleHit);
				GetWorldTimerManager().SetTimer(outHandleHit, this, &AGeneralCharacter::ResetHit, GetWorld()->GetDeltaSeconds(), false);
			}
			else
			{
				isHit = true;
				GetWorldTimerManager().SetTimer(outHandleHit, this, &AGeneralCharacter::ResetHit, recoveryTime, false);
			}
		}
		// particle
		if (onHitParticle)
		{
			UGameplayStatics::SpawnEmitterAttached(onHitParticle, GetRootComponent());
		}
	}

	if (life <= 0)
	{
		isAlive = false;
		GameOverEvent();

		if (myDoor != nullptr)
			myDoor->AddToCount();
	}
}
void AGeneralCharacter::ResetHit()
{
	if (!isHit)
	{
		isHit = true;
		GetWorldTimerManager().ClearTimer(outHandleHit);
		GetWorldTimerManager().SetTimer(outHandleHit, this, &AGeneralCharacter::ResetHit, recoveryTime, false);
	}
	stun = false;
	isHit = false;
}

void AGeneralCharacter::ActivateAttackComponent()
{
	hasMissed = true;
}

void AGeneralCharacter::DeactivateAttackComponent()
{

}

void AGeneralCharacter::Attack()
{
	if (canAttack)
	{
		OnAttack.Broadcast();
		if (!canMoveOnAttack)
		{
			GetCharacterMovement()->MaxWalkSpeed = 0;
			GetCharacterMovement()->RotationRate = { 0, 0, 0 };
		}
		canAttack = false;
		FTimerHandle _outHandleDash;
		GetWorldTimerManager().SetTimer(_outHandleDash, this, &AGeneralCharacter::ResetAttack, 1 / attackSpeed, false);
	}
}

void AGeneralCharacter::EndAttack()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	GetCharacterMovement()->RotationRate = rotationRate;
}

void AGeneralCharacter::ResetAttack()
{
	canAttack = true;
}

void AGeneralCharacter::GameOverEvent_Implementation()
{
	isAlive = false;
}

void AGeneralCharacter::TargetEvent_Implementation()
{

}

// ================================ OverLap Function ================================ //


void AGeneralCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

}

void AGeneralCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<UAreaDamage>(OtherComp))
	{
		
		areaDamage = Cast<UAreaDamage>(OtherComp);

			if (areaDamage->IsOverlappingComponent(GetCapsuleComponent()))
			{
				return;
			}
			else
			{
				areaDamage = nullptr;
			}
		
	}
}

void AGeneralCharacter::TakeDamageByArea()
{
	if (areaDamage == nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		return;
	}

	timerCoolDown -= GetWorld()->DeltaTimeSeconds;

	if (timerCoolDown < 0)
	{
		timerCoolDown = areaDamage->coolDown;
		this->ModifyLife(-areaDamage->damageTaken, areaDamage->team, false);
	}
}

AGeneralCharacter* AGeneralCharacter::FindCharacterByIndex(int index)
{
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneralCharacter::StaticClass(), FoundCharacters);
	
	for (AActor* myActor : FoundCharacters)
	{
		AGeneralCharacter* myCharacter = Cast<AGeneralCharacter>(myActor);

		if (myCharacter->indexSave == index)
			return myCharacter;
	}

	return NULL;
}

void AGeneralCharacter::SetIsAlive(bool onOff)
{
	this->isAlive = onOff;
}

void AGeneralCharacter::CheckIsAliveToCheckPoint()
{
	if (isAlive)
	{
		life = maxLife;
	}
	else
	{
		life = 0;

		GameOverEvent();

		if (myDoor != nullptr)
			myDoor->AddToCount();
	}
}
