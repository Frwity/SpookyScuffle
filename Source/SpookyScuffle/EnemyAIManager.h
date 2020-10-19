// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAIManager.generated.h"

UCLASS()
class SPOOKYSCUFFLE_API AEnemyAIManager : public AActor
{
	GENERATED_BODY()

protected:
	
	class AGeneralCharacter* player;

	class TArray<class AEnemyAIController*> enemyAIs;

	virtual void BeginPlay() override;

public:	
	
	AEnemyAIManager();

	virtual void Tick(float DeltaTime) override;

	void AddEnemyAI(class AEnemyAIController*);
	void RemoveEnemyAI(class AEnemyAIController*);
};