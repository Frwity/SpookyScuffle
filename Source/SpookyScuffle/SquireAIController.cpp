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

}

void ASquireAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (!isAlive)
		return;
}