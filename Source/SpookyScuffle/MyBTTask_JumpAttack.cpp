// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_JumpAttack.h"
#include "KnightCharacter.h"
#include "EnemyAIController.h"
#include "AIController.h"

EBTNodeResult::Type UMyBTTask_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AKnightCharacter* knight = Cast<AKnightCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!knight->CanAttackJump())
		return EBTNodeResult::Failed;
	knight->AttackJump(Cast<AEnemyAIController>(OwnerComp.GetAIOwner())->GetTargetPos(), Cast<AEnemyAIController>(OwnerComp.GetAIOwner())->GetTargetDir());
	return EBTNodeResult::Succeeded;
}

