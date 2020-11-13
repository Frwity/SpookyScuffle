// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorEnemy.generated.h"

UCLASS()
class SPOOKYSCUFFLE_API ADoorEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADoorEnemy();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Door, meta = (AllowPrivateAccess = "true"))
		FVector axisMovement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Door, meta = (AllowPrivateAccess = "true"))
		float speedDoor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Door, meta = (AllowPrivateAccess = "true"))
		float distanceDoorOpen;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Door, meta = (AllowPrivateAccess = "true"))
		bool followUnlock; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Door, meta = (AllowPrivateAccess = "true"))
		bool giveExtraLife = false;


	int goalToUnlock = 0;
	bool unlock = false;
	FTimerHandle timerOpenDoor;
	FVector savePos;

	bool isGetPlayer = false;
	class ASpookyScuffleCharacter* player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int countToUnlock = 0;

	void SetGoalToUnlock();
	void AddToCount();
	void OpenTheDoor();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		void StartVibrating() ;
	void StartVibrating_Implementation() {};
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		void StopVibrating() ;
	void StopVibrating_Implementation() {};

	// =============== CheckPoint =============== //

	int indexSave;
};
