// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"


void AKnightCharacter::AttackJump(float force)
{
	if (!canAttackJump)
		return;
	
	canAttackJump = false;
	isAttackJumping = true;

	GetCharacterMovement()->Launch(GetCapsuleComponent()->GetForwardVector().RotateAngleAxis(-10, GetCapsuleComponent()->GetRightVector()) * force * 3.5);

	FTimerHandle _timeHandle;
	GetWorldTimerManager().SetTimer(_timeHandle, this, &AKnightCharacter::ResetAttackJump, jumpCD, false);
}

void AKnightCharacter::ResetAttackJump()
{
	canAttackJump = true;
}

void AKnightCharacter::EndAttackJump()
{
	isAttackJumping = false;
}