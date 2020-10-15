// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"
#include "GeneralCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Cast<AGeneralCharacter>(OwnerComp.GetAIOwner()->GetPawn())->Attack();
	return EBTNodeResult::Succeeded;
}

