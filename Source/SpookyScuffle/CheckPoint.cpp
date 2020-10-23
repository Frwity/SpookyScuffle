// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"
#include "SaveGameSpooky.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPoint::CheckIsOk()
{
	if (!isCheck)
	{
		isCheck = true;

		GEngine->AddOnScreenDebugMessage(1, 4, FColor::Cyan, TEXT("checkpoint WIP"));
	}
}

void ACheckPoint::LoadGameAtCheckPoint()
{
	
}
