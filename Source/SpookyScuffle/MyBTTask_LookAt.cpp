// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_LookAt.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GeneralCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UMyBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector targetPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);;
	FVector enemyPos = Cast<AGeneralCharacter>(OwnerComp.GetAIOwner()->GetPawn())->GetActorLocation();
	targetPos.Z = enemyPos.Z = 0;

	OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(enemyPos, targetPos));


	return EBTNodeResult::Succeeded;
}