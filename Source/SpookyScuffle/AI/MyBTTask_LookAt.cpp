// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_LookAt.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Character/GeneralCharacter.h"
#include "AIController.h"


EBTNodeResult::Type UMyBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* enemy = OwnerComp.GetAIOwner()->GetPawn();
	FVector targetPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);;
	FVector enemyPos = enemy->GetActorLocation();
	targetPos.Z = enemyPos.Z = 0;

	targetPos = FMath::Lerp(enemyPos + enemy->GetActorForwardVector() * 1, targetPos, 0.007);

	OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(enemyPos, targetPos));


	return EBTNodeResult::Succeeded;
}