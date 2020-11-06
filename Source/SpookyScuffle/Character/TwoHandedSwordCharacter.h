// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralCharacter.h"
#include "TwoHandedSwordCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API ATwoHandedSwordCharacter : public AGeneralCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

	virtual void MoveForward(float _value) override;
	virtual void MoveRight(float _value) override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* rightWeaponMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* leftWeaponMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAttackComponent* rightAttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAttackComponent* leftAttackComponent;

public:	
	ATwoHandedSwordCharacter();

	virtual void ModifyLife(int _lifePoint, E_TEAMS _team, bool _stun) override;

	virtual void ActivateAttackComponent() override;
	virtual void DeactivateAttackComponent() override;

	virtual void Attack() override;

	virtual void GameOverEvent_Implementation() override;
};
