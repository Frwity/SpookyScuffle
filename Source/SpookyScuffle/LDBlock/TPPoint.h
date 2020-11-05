// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPPoint.generated.h"

UCLASS()
class SPOOKYSCUFFLE_API ATPPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPPoint();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TPPoint, meta = (AllowPrivateAccess = "true"))
		int pointNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
