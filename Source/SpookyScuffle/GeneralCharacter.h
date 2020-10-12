// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Character.h"
#include "GeneralCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiDynDelegate);
// you can find Event in Event Graph of doublesword Animation

UENUM()
enum class E_TEAMS
{
	Ally,
	Enemy
};

UCLASS()
class SPOOKYSCUFFLE_API AGeneralCharacter : public ACharacter
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

	virtual int GetLife() { return life; }
	virtual int GetDamage() { return damage; }
	virtual bool IsAlive() { return isAlive; }
	virtual E_TEAMS GetTeam() { return team; }

	virtual void ModifyLife(int _lifePoint, E_TEAMS _team);

	UFUNCTION(BlueprintCallable)
	virtual void ActivateAttackComponent();
	UFUNCTION(BlueprintCallable)
	virtual void DeactivateAttackComponent();

	UFUNCTION()
	virtual void Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void GameOverEvent();
		void GameOverEvent_Implementation();
};

	




