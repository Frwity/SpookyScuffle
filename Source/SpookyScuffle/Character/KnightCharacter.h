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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpAttack, meta = (AllowPrivateAccess = "true"))
		float jumpTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpAttack, meta = (AllowPrivateAccess = "true"))
		float jumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpAttack, meta = (AllowPrivateAccess = "true"))
		float anticipationMultiplicator;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = JumpAttack, meta = (AllowPrivateAccess = "true"))
		bool isAttackJumping = false;

	float currentJumpTime = 0.f;
	FVector offset;
	float zOffset1;
	float zOffset2;
	float zCurrentOffset1;
	float zCurrentOffset2;

	FVector target;

	bool canAttackJump = true;

	FTimerHandle jumpTimeHandler;


public:

	void Tick(float _deltaTime) override;
	void BeginPlay() override;

	float GetJumpCD() { return jumpCD; }
	
	bool IsAttackJumping() { return isAttackJumping; }

	bool CanAttackJump() { return canAttackJump; }

	void AttackJump(FVector, FVector);
	void Jumping();
	void ResetAttackJump();
};
