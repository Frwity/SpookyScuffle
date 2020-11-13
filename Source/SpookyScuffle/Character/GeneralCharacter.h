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
	Enemy,
	Environement
};

UCLASS()
class SPOOKYSCUFFLE_API AGeneralCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		E_TEAMS team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		int maxLife = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		int life = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		float invulnerabilityTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		float invulnerabilityCD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		bool isHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		float recoveryTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		bool isAlive = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NormalAttack, meta = (AllowPrivateAccess = "true"))
		float attackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NormalAttack, meta = (AllowPrivateAccess = "true"))
		bool canAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalAttack, meta = (AllowPrivateAccess = "true"))
		int damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NormalAttack, meta = (AllowPrivateAccess = "true"))
		bool canMoveOnAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NormalAttack, meta = (AllowPrivateAccess = "true"))
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* onHitParticle;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FMultiDynDelegate OnAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door, meta = (AllowPrivateAccess = "true"))
		class ADoorEnemy* myDoor;


	// ==================================== Area Damage ==================================== //

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AreaDamage, meta = (AllowPrivateAccess = "true"))
	class UAreaDamage* areaDamage;
	FTimerHandle outHandleHit;
	FTimerHandle timerHandle;
	FTimerHandle attackTimeHandler;


	bool stopTimer = false;
	float timerCoolDown;


	// ======================================================================== //

	float walkSpeed;
	FRotator rotationRate;
	FTimerHandle timerLife;

	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

	virtual void MoveForward(float _value);
	virtual void MoveRight(float _value);

public:	

	AGeneralCharacter();

	virtual int GetLife() { return life; }
	virtual int GetDamage() { return damage; }
	virtual bool IsAlive() { return isAlive; }
	virtual bool IsHit() { return isHit; }
	virtual E_TEAMS GetTeam() { return team; }
	
	virtual void ModifyLife(int _lifePoint, E_TEAMS _team, bool _stun);

	void ResetHit();

	UFUNCTION(BlueprintCallable)
		virtual void ActivateAttackComponent();
	UFUNCTION(BlueprintCallable)
		virtual void DeactivateAttackComponent();
	
	UFUNCTION()
		virtual void Attack();
	UFUNCTION(BlueprintCallable)
		virtual void EndAttack();
	virtual void ResetAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void GameOverEvent();
	virtual void GameOverEvent_Implementation();

	void SetCanAttack(bool onOff) { canAttack = onOff; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool stun = false;

	UPROPERTY(BlueprintReadOnly)
		bool hasMissed = true;

	void MaxLifeAgain();

	// ==================================== Area Damage ==================================== //

	void TakeDamageByArea();

	// ==================================== CheckPoint ==================================== //

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myCheckPoint, meta = (AllowPrivateAccess = "true"))
		int saveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myCheckPoint, meta = (AllowPrivateAccess = "true"))
		int indexSave;

	void SetIsAlive(bool onOff);
	void CheckIsAliveToCheckPoint();
	AGeneralCharacter* FindCharacterByIndex(int index);

	// ==================================== Target ==================================== //

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool isLock = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TargetEvent();
	virtual void TargetEvent_Implementation();

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

	




