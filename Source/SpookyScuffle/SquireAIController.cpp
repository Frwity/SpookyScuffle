// Fill out your copyright notice in the Description page of Project Settings.


#include "SquireAIController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GeneralCharacter.h"
#include "SquireCharacter.h"
#include "Engine/Engine.h"



void ASquireAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);

	Player = Cast<AGeneralCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	ASquireCharacter* enemy = Cast<ASquireCharacter>(GetPawn());

	Blackboard->SetValueAsFloat(TEXT("TriggerDistance"), enemy->GetTriggerDistance());
	Blackboard->SetValueAsFloat(TEXT("AttackDistance"), enemy->GetAttackDistance());
}

void ASquireAIController::Tick(float deltaTime)
{
	isAlive = Cast<AGeneralCharacter>(GetPawn())->IsAlive();
	Blackboard->SetValueAsBool(TEXT("IsAlive"), isAlive);
	if (!isAlive)
		return;

	FVector enemyPos = GetPawn()->GetActorLocation();
	FVector playerPos = Player->GetActorLocation();
	FVector away = 2 * enemyPos - playerPos;

	Blackboard->SetValueAsVector(TEXT("PlayerPos"), playerPos);
	Blackboard->SetValueAsVector(TEXT("AwayFromPlayer"), enemyPos + ((away - enemyPos).GetSafeNormal() * 500));
}