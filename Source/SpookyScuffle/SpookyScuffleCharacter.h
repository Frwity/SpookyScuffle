// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TwoHandedSwordCharacter.h"
#include "SpookyScuffleCharacter.generated.h"

UCLASS(config=Game)
class ASpookyScuffleCharacter : public ATwoHandedSwordCharacter
{

	GENERATED_BODY()

private:

	// ================================== DASH ================================== //

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true", 
			  ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float distanceDash = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float speedDash = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float coolDownDash = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float isDash = false;

		float timerDash = 0;
		float timerCoolDownDash = 0;
		bool isCoolDownDash = false;

		FVector savePosDash;
		FTimerHandle outHandleDash;

	// ================================== Lock ================================== //

		bool loadLock = false;
		class AGeneralCharacter* enemyToLock;
		float distanceMaxLock = 2000;
		float angleLock = 60;


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
	void ActivateDash();
	void DashMovement();
	void ActivateLock();
	void DisableLock();
	bool CheckEnemyToLock(FVector enemy, FVector posPlayer);


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

