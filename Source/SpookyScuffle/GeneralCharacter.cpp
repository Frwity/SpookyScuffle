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
}

void AGeneralCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (invulnerabilityCD >= 0)
		invulnerabilityCD -= _deltaTime;
}

void AGeneralCharacter::MoveForward(float _value)
{
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

void AGeneralCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	if (invulnerabilityCD >= 0 || !isAlive)
		return;

	if (_lifePoint < 0 && team != _team)
	{
		invulnerabilityCD = invulnerabilityTime;
		life += _lifePoint;


		// particle
		if (onHitParticle)
		{
			UGameplayStatics::SpawnEmitterAttached(onHitParticle, GetRootComponent());
		}
	}

	if (life <= 0)
	{
		GameOverEvent();
	}
}

void AGeneralCharacter::ActivateAttackComponent()
{

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
			GetCharacterMovement()->MaxWalkSpeed = 0;
		canAttack = false;
		FTimerHandle _outHandleDash;
		GetWorldTimerManager().SetTimer(_outHandleDash, this, &AGeneralCharacter::ResetAttack, 1 / attackSpeed, false);
	}
}

void AGeneralCharacter::EndAttack()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AGeneralCharacter::ResetAttack()
{
	canAttack = true;
}

void AGeneralCharacter::GameOverEvent_Implementation()
{
	isAlive = false;
}