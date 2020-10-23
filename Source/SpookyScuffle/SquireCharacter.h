// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OneHandedSwordCharacter.h"
#include "SquireCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API ASquireCharacter : public AOneHandedSwordCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float triggerDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float attackDistance;

public:

	ASquireCharacter();

	float GetTriggerDistance() { return triggerDistance; }
	float GetAttackDistance() { return attackDistance; }

};