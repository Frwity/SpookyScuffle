// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterInterface.h"
#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Character.h"
#include "GeneralCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiDynDelegate);

UCLASS()
class SPOOKYSCUFFLE_API AGeneralCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	E_TEAMS team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	int maxLife;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	int life;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	float invulnerabilityTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	float invulnerabilityCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	int damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	bool isAlive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* onHitParticle;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMultiDynDelegate OnAttack;


	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

	virtual void MoveForward(float _value);
	virtual void MoveRight(float _value);

public:	
	AGeneralCharacter();

	
	virtual int GetLife() override { return life; }
	virtual int GetDamage() override { return damage; }
	virtual bool IsAlive() override { return isAlive; }
	virtual E_TEAMS GetTeam() override { return team; }

	virtual void ModifyLife(int _lifePoint, E_TEAMS _team) override;

	UFUNCTION()
	virtual void Attack();
};

	




