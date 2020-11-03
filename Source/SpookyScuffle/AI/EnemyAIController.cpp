// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyAIManager.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../Character/GeneralCharacter.h"
#include "Engine/Engine.h"



void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);

	player = Cast<AGeneralCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	enemy = Cast<AGeneralCharacter>(GetPawn());

	Blackboard->SetValueAsFloat(TEXT("TriggerDistance"), triggerDistance);
	Blackboard->SetValueAsFloat(TEXT("SafeDistance"), safeDistance);
	Blackboard->SetValueAsFloat(TEXT("AttackDistance"), attackDistance);	
}

void AEnemyAIController::Tick(float deltaTime)
{
	if (!enemy->IsAlive() && isAlive)
		enemyAIManager->RemoveEnemyAI(this);

	isAlive = enemy->IsAlive();
	Blackboard->SetValueAsBool(TEXT("IsAlive"), isAlive);
	if (!isAlive)
		return;

	isLock = enemy->isLock;

	FVector enemyPos = GetPawn()->GetActorLocation();
	FVector playerPos = player->GetActorLocation();
	targetDir = player->GetActorForwardVector();
	FVector away = 2 * enemyPos - playerPos;


	if (FVector::Dist(playerPos, enemyPos) < triggerDistance)
	{
		if (!isTriggered && isPartOfCrowd)
			enemyAIManager->AddEnemyAI(this);
		isTriggered = true;
	}
	else
	{
		if (isTriggered && isPartOfCrowd)
			enemyAIManager->RemoveEnemyAI(this);
		isTriggered = false;
	}

	if (!isPartOfCrowd)
		targetPos = playerPos;


	Blackboard->SetValueAsVector(TEXT("TargetPos"), targetPos);
	Blackboard->SetValueAsVector(TEXT("PlayerPos"), playerPos);
	Blackboard->SetValueAsVector(TEXT("AwayFromPlayer"), enemyPos + ((away - enemyPos).GetSafeNormal() * 500));
	Blackboard->SetValueAsBool(TEXT("Stun"), enemy->stun);
}