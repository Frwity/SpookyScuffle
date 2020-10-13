// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralCharacter.h"
#include "OneHandedSwordCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AOneHandedSwordCharacter : public AGeneralCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

	virtual void MoveForward(float _value) override;
	virtual void MoveRight(float _value) override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* weaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UAttackComponent* attackComponent;

public:
	AOneHandedSwordCharacter();

	virtual void ModifyLife(int _lifePoint, E_TEAMS _team) override;

	virtual void ActivateAttackComponent() override;
	virtual void DeactivateAttackComponent() override;

	virtual void Attack() override;
};
