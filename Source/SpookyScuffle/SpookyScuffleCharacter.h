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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option, meta = (AllowPrivateAccess = "true"))
		bool playerCanJump = true;

	// ================================== DASH ================================== //

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true", 
			  ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float distanceDash = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float speedDash = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float coolDownDash = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		bool isDash = false;

		float timerDash = 0;
		float timerCoolDownDash = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		bool isCoolDownDash = false;

		FVector savePosDash;
		FTimerHandle outHandleDash;

	// ================================== Lock ================================== //

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lock , meta = (AllowPrivateAccess = "true"))
			bool loadLock = false;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lock , meta = (AllowPrivateAccess = "true"))
			class AGeneralCharacter* enemyToLock;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lock, meta = (AllowPrivateAccess = "true"))
			float distanceMaxLock = 2000;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lock, meta = (AllowPrivateAccess = "true"))
			float angleLock = 60;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lock, meta = (AllowPrivateAccess = "true"))
			float speedCameraLock = 100;
		
		float saveArmLength;
		float saveMaxAngleLock;
		bool passToDisable = false;
		
		FTimerHandle outHandleLock;
		FTimerHandle outHandleExitLock;

	// ================================== Bat Form ================================== //

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BatForm, meta = (AllowPrivateAccess = "true"))
			bool isBatMode = false;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BatForm, meta = (AllowPrivateAccess = "true"))
			float mutiplySpeedBatMode = 1.5f;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BatForm, meta = (AllowPrivateAccess = "true"))
			float timerBatLostLife = 1.5f;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BatForm, meta = (AllowPrivateAccess = "true"))
			int costTransformToBat = 2;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BatForm, meta = (AllowPrivateAccess = "true"))
			int costBatForm = 1;

		float saveTimerBLL;
		FTimerHandle outHandleBatForm;

	// ================================== Special Attack ================================== //

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			class AGeneralCharacter* enemyToEat;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			bool useIsDrain = false;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			float distanceMaxToDrain = 500;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			float speedSpecialAttack = 500;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			int drainHowManyLife = 1;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			float timerDrainLife = 0.5f;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpecialAttack, meta = (AllowPrivateAccess = "true"))
			float mutiplySpeedSpecialAttack = 5.f;

		bool drainBlood = false;
		float saveTimerDL;
		int saveLifePLayerOnDrain;
		FTimerHandle outHandleSpecialAttack;

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

	// === Dash
	void ActivateDash();
	void DashMovement();

	// === Lock
	void ActivateLock();
	void DisableLock();
	bool CheckEnemyToLock(FVector enemy, FVector posPlayer);
	void LockEnemy();
	void ExitLock();

	// === Bat Form
	void SetBatMode();
	void tickLostLifeBatForm();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void BatEvent();
	void BatEvent_Implementation();

	// === Special Attack
	void ActivateSpecialAttack();
	void SpecialAttackMove();
	void SpecialAttackDrain();
	void ResetDrainValue();


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

