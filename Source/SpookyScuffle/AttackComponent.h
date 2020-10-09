// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "AttackComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API UAttackComponent : public UBoxComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	UAttackComponent();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
