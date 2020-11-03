// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "VillagerAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AVillagerAIController : public AEnemyAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

};
