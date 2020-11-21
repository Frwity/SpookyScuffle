// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"



void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKnightCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void AKnightCharacter::AttackJump(FVector _target, FVector _direction)
{
	if (!canAttackJump)
		return;
	
	canAttackJump = false;
	isAttackJumping = true;

	target = _target + _direction * anticipationMultiplicator * 10;

	currentJumpTime = 0.0f;

	offset = (target - GetActorLocation()) / (jumpTime / GetWorld()->GetDeltaSeconds());

	zOffset1 = (target.Z - GetActorLocation().Z + jumpHeight) / ((jumpTime / 2) / GetWorld()->GetDeltaSeconds());
	zCurrentOffset1 = zOffset1 * 3;
	zOffset2 = (-jumpHeight) / ((jumpTime / 2) / GetWorld()->GetDeltaSeconds());
	zCurrentOffset2 = 0;
	GetWorldTimerManager().SetTimer(jumpTimeHandler, this, &AKnightCharacter::Jumping, GetWorld()->GetDeltaSeconds(), true);

	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;

	FTimerHandle _timeHandle2;
	GetWorldTimerManager().SetTimer(_timeHandle2, this, &AKnightCharacter::ResetAttackJump, jumpCD, false);
}

void AKnightCharacter::Jumping()
{
	currentJumpTime += GetWorld()->GetDeltaSeconds();
	FHitResult OutHit;

	if (currentJumpTime >= jumpTime
	||  GetWorld()->LineTraceSingleByChannel(OUT OutHit, GetActorLocation(), GetActorLocation() - FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 10), ECC_Visibility)
	&& currentJumpTime > jumpTime / 2)
	{
		GetWorldTimerManager().ClearTimer(jumpTimeHandler);
		isAttackJumping = false;
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Falling;
		GetCharacterMovement()->GravityScale = 1;
		return;
	}

	if (currentJumpTime <= jumpTime / 2)
	{
		zCurrentOffset1 = FMath::Lerp(zCurrentOffset1, zOffset1 / 3, 0.1f);
		offset.Z = zCurrentOffset1;
	}
	else 
	{
		zCurrentOffset2 = FMath::Lerp(zCurrentOffset2, zOffset2, 0.3f);
		offset.Z = zCurrentOffset2;
	}
	AddActorWorldOffset(offset);
}

void AKnightCharacter::ResetAttackJump()
{
	canAttackJump = true;
}