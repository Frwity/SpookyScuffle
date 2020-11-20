// Fill out your copyright notice in the Description page of Project Settings.


#include "BowmanCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


ABowmanCharacter::ABowmanCharacter()
	: AGeneralCharacter{}
{
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));;
	weaponMesh->SetupAttachment(GetMesh(), FName("LeftWeaponShield"));

}

void ABowmanCharacter::Attack()
{
	Super::Attack();
	targetPos = Cast<AGeneralCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetActorLocation();
}