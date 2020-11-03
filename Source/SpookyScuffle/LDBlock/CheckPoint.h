// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

UCLASS()
class SPOOKYSCUFFLE_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Option, meta = (AllowPrivateAccess = "true"))
		int orderCheckPoint = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isCheck = false;

	// ================================== Data ================================== //

	//all character
	TArray<FTransform> transformCharacter;
	TArray<bool> isAliveCharacter;

	void SaveDataCharacters();
	void LoadDataCharacters();

	// door
	TArray<FVector> savePosDoor;

	void SaveDataDoor();
	void LoadDataDoor();
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckIsOk();
	bool IsCheck() { return isCheck;}

	UFUNCTION(BlueprintCallable)
		void LoadGameAtCheckPoint();


};
