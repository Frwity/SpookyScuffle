// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_IsAtDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../Character/GeneralCharacter.h"
#include "AIController.h"

bool UMyBTDecorator_IsAtDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	FVector playerPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerPos"));
	AGeneralCharacter* enemy = Cast<AGeneralCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	float distance = FVector::Dist(playerPos, enemy->GetActorLocation());

	if (distance < OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BlackboardKey.SelectedKeyName))
		return true;
	else
		return false;
}
