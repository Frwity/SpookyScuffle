// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MoveToLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


EBTNodeResult::Type UMyBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector destination = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);

	EPathFollowingRequestResult::Type destinationTest = OwnerComp.GetAIOwner()->MoveToLocation(destination, true);

	if (destinationTest == EPathFollowingRequestResult::Type::RequestSuccessful
	||  destinationTest == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		return EBTNodeResult::Succeeded;
	else
		return EBTNodeResult::Failed;
}
