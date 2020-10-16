// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerAIController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GeneralCharacter.h"
#include "VillagerCharacter.h"
#include "Engine/Engine.h"



void AVillagerAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);

	Player = Cast<AGeneralCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AVillagerCharacter* enemy = Cast<AVillagerCharacter>(GetPawn());

	Blackboard->SetValueAsFloat(TEXT("SafeDistance"), enemy->GetSafeDistance());
	Blackboard->SetValueAsFloat(TEXT("FleeTriggerDistance"), enemy->GetFleeTriggerDistance());
}

void AVillagerAIController::Tick(float deltaTime)
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
	bool _stun = Cast<AGeneralCharacter>(GetPawn())->stun;
	Blackboard->SetValueAsBool(TEXT("Stun"), _stun);
}