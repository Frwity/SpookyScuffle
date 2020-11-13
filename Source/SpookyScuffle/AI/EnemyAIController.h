// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:

	bool isAlive;
	bool isTriggered;
	bool isLock;

	bool end;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		bool isPartOfCrowd = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float triggerDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float attackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float safeDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float targetToleranceMin;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		float targetToleranceMax;
	float targetTolerance;

	FVector targetPos;
	FVector targetDir;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	FVector targetStrafe;

	class AGeneralCharacter* enemy;
	class AGeneralCharacter* player;

	class AEnemyAIManager* enemyAIManager;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

public:

	bool isAFighter;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviourTree;

	void SetTargetPos(FVector newTargetPos) { targetPos = newTargetPos; }
	void SetEnemyAIManager(class AEnemyAIManager* newEnemyAIManager) { enemyAIManager = newEnemyAIManager; }

	FVector GetTargetPos() { return targetPos; }
	FVector GetTargetDir() { return targetDir; }

	bool IsLock() { return isLock; }

	float GetSafeDistance() { return safeDistance; }
};

