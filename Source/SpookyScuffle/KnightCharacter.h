// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwoHandedSwordCharacter.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AKnightCharacter : public ATwoHandedSwordCharacter
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpAttack, meta = (AllowPrivateAccess = "true"))
		float jumpCD;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = JumpAttack, meta = (AllowPrivateAccess = "true"))
		bool isAttackJumping = false;

	bool canAttackJump = true;

public:

	float GetJumpCD() { return jumpCD; }
	
	bool IsAttackJumping() { return isAttackJumping; }

	bool CanAttackJump() { return canAttackJump; }

	void AttackJump(float);
	void ResetAttackJump();
	void EndAttackJump();
};
