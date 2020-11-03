// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_IsAtDistance.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API UMyBTDecorator_IsAtDistance : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

		virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
