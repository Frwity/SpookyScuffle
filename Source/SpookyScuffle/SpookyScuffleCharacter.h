// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CharacterInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpookyScuffleCharacter.generated.h"

UCLASS(config=Game)
class ASpookyScuffleCharacter : public ACharacter, public ICharacterInterface
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	E_TEAMS team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	int maxLife;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	int life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	int damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	bool isAlive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* onHitParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;

	virtual void Tick(float _deltaTime) override;

	virtual void BeginPlay() override;

	void MoveForward(float _value);
	void MoveRight(float _value);
	void TurnAtRate(float _rate);
	void LookUpAtRate(float _rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;

public:

	ASpookyScuffleCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float baseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float baseLookUpRate;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return followCamera; }

	int GetDamage() override { return damage; }
	int GetLife() override { return life; }
	E_TEAMS GetTeam() override { return team; }
	bool IsAlive() { return isAlive; }
	void ModifyLife(int _lifePoint, E_TEAMS _team) override;

};

