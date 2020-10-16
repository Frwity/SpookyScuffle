// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaDamage.h"
#include "GeneralCharacter.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"



UAreaDamage::UAreaDamage()
{
}

void UAreaDamage::BeginPlay()
{
	Super::BeginPlay();

	saveCoolDown = coolDown;

	OnComponentBeginOverlap.AddDynamic(this, &UAreaDamage::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UAreaDamage::OnOverlapEnd);

}

void UAreaDamage::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	saveCharacter = Cast<AGeneralCharacter>(OtherActor);
	saveCharacter->ModifyLife(-damageTaken, E_TEAMS::Environement);
		
	GetWorld()->GetTimerManager().SetTimer(outHandleTimer, this, &UAreaDamage::TakeDamage, GetWorld()->GetDeltaSeconds(), true);
}

void UAreaDamage::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	stopTimer = true;
}

void UAreaDamage::TakeDamage()
{
	coolDown -= GetWorld()->DeltaTimeSeconds;

	if (coolDown < 0)
	{
		coolDown = saveCoolDown;
		saveCharacter->ModifyLife(-damageTaken, E_TEAMS::Environement);
	}

	if (stopTimer)
	{
		stopTimer = false;
		GetWorld()->GetTimerManager().ClearTimer(outHandleTimer);
	}
}