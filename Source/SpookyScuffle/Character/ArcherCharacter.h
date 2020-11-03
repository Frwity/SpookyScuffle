// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BowmanCharacter.h"
#include "ArcherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AArcherCharacter : public ABowmanCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NormalAttack, meta = (AllowPrivateAccess = "true"))
		float attackRange = 0.0f;

public:

	float GetAttackRange() { return attackRange; }
};
