// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SquireAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API ASquireAIController : public AAIController
{
	GENERATED_BODY()

protected:

	bool isAlive;

	class AGeneralCharacter* Player;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviourTree;
};