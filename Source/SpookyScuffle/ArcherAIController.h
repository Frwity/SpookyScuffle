// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "ArcherAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AArcherAIController : public AEnemyAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

};