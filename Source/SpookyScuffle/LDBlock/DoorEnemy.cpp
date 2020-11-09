// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorEnemy.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/SpookyScuffleCharacter.h"

// Sets default values
ADoorEnemy::ADoorEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorEnemy::BeginPlay()
{
	Super::BeginPlay();
	savePos = GetActorLocation();
}

// Called every frame
void ADoorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorEnemy::SetGoalToUnlock()
{
	goalToUnlock += 1;
}

void ADoorEnemy::AddToCount()
{
	countToUnlock += 1;

	if (countToUnlock >= goalToUnlock && !unlock)
	{
		StartVibrating();
		GetWorldTimerManager().SetTimer(timerOpenDoor, this, &ADoorEnemy::OpenTheDoor, GetWorld()->GetDeltaSeconds(), true);
	}
}

void ADoorEnemy::OpenTheDoor()
{
	if (!unlock)
	{
		if (!isGetPlayer)
		{
			isGetPlayer = true;
			player = Cast<ASpookyScuffleCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpookyScuffleCharacter::StaticClass()));
		}

		FVector _posDoor;

		if ((savePos - GetActorLocation()).Size() < distanceDoorOpen)
		{
			_posDoor = axisMovement * (speedDoor * GetWorld()->DeltaTimeSeconds);

			SetActorLocation(GetActorLocation() + _posDoor);

			if (followUnlock)
				player->LockPosition(GetActorLocation());
			else
			{
				player->LockPosition(savePos);
			}
		}
		else
		{
			StopVibrating();

			if (player->ExitLockCondition())
			{
				unlock = true;
				GetWorldTimerManager().ClearTimer(timerOpenDoor);
			}
		}
	}
}

