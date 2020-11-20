// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralCharacter.h"
#include "BowmanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API ABowmanCharacter : public AGeneralCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector targetPos;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* weaponMesh;

public:
	ABowmanCharacter();

	void Attack() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Fire();
	virtual void Fire_Implementation() {}
};
