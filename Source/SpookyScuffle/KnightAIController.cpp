	// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightAIController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GeneralCharacter.h"
#include "KnightCharacter.h"
#include "Engine/Engine.h"



void AKnightAIController::BeginPlay()
{
	Super::BeginPlay();

	startPos = enemy->GetActorLocation();
	Blackboard->SetValueAsVector(TEXT("StartPos"), startPos);
	Blackboard->SetValueAsFloat(TEXT("JumpDistance"), jumpDistance);
}

void AKnightAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (!isAlive)
		return;

	Blackboard->SetValueAsBool(TEXT("IsAttackJumping"), Cast<AKnightCharacter>(GetPawn())->IsAttackJumping());
	
}
