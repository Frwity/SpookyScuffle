// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/GeneralCharacter.h"
#include "Components/BoxComponent.h"
#include "AreaDamage.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API UAreaDamage : public UBoxComponent
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

public:

	UAreaDamage();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option, meta = (AllowPrivateAccess = "true"))
		int damageTaken = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option, meta = (AllowPrivateAccess = "true"))
		float coolDown = 0.4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option, meta = (AllowPrivateAccess = "true"))
		E_TEAMS team;

};
