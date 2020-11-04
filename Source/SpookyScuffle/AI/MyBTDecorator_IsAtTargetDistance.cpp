// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_IsAtTargetDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../Character/GeneralCharacter.h"
#include "AIController.h"

bool UMyBTDecorator_IsAtTargetDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	FVector targetPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TargetPos"));
	AGeneralCharacter* enemy = Cast<AGeneralCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	float distance = FVector::Dist(targetPos, enemy->GetActorLocation());

	if (distance < OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BlackboardKey.SelectedKeyName))
		return true;
	else
		return false;
}
