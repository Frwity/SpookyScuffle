// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TwoHandedSwordCharacter.h"
#include "SpookyScuffleCharacter.generated.h"

UCLASS(config=Game)
class ASpookyScuffleCharacter : public ATwoHandedSwordCharacter
{

	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;

	virtual void Tick(float _deltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;

	void MoveForward(float _value) final;
	void MoveRight(float _value) override;
	void TurnAtRate(float _rate);
	void LookUpAtRate(float _rate);


public:

	ASpookyScuffleCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float baseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float baseLookUpRate;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return followCamera; }

	int GetLife() final { return life; }
	int GetDamage() final { return damage; }
	bool IsAlive() final { return isAlive; }
	E_TEAMS GetTeam() final { return team; }

	void ModifyLife(int _lifePoint, E_TEAMS _team) final;

	void Attack() final;
};

