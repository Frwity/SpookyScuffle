// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandFreeCharacter.h"
#include "VillagerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AVillagerCharacter : public AHandFreeCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float safeDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float fleeTriggerDistance;

public:

	AVillagerCharacter();

	float GetSafeDistance() { return safeDistance; }
	float GetFleeTriggerDistance() { return fleeTriggerDistance; }
};
