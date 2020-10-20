// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "KnightAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AKnightAIController : public AEnemyAIController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float jumpDistance;

	FVector startPos;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

};
