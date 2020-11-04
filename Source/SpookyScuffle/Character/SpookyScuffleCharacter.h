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
	// ================================== Option ================================== //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option, meta = (AllowPrivateAccess = "true"))
		bool playerCanJump = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Option, meta = (AllowPrivateAccess = "true"))
		bool playerMovable = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Option, meta = (AllowPrivateAccess = "true"))
		class ACheckPoint* myCheckPoint;

	// ================================== Camera ================================== //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		bool blockCameraPitch = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float speedRotCam = 40;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float axisCam = 344;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float limitPitch = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		bool unlockPitch = false;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		bool isCoolDownDash = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float slowSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
		float slowTime;
	bool isSlowDash;
	
	float timerDash = 0;
	float timerCoolDownDash = 0;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lock, meta = (AllowPrivateAccess = "true"))
		float limitUpCamera = 500;
		
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
	bool stopDrain = false;
	float timerSecuritySP = 2;
	float saveTimerSecuritySP;
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
	void ResetDashSpeed();

	// === Lock
	void ActivateLock();
	void DisableLock();
	bool CheckEnemyToLock(FVector enemy, FVector posPlayer, FVector forwardVec);
	void LockEnemy();
	void ExitLock();

	// === Bat Form
	void SetBatMode();
	void UnSetBatMode();
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void YouWinEvent();
		void YouWinEvent_Implementation();

		bool youWin = false;

	virtual void GameOverEvent_Implementation() override;


	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};

