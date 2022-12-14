// Fill out your copyright notice in the Description page of Project Settings.


#include "OneHandedSwordCharacter.h"
#include "AttackComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


AOneHandedSwordCharacter::AOneHandedSwordCharacter()
	: AGeneralCharacter{}
{
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));;
	weaponMesh->SetupAttachment(GetMesh(), FName("RightWeaponShield"));
	
	attackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	attackComponent->SetupAttachment(weaponMesh);
	attackComponent->SetRelativeLocation({ 0,0,0 });
	attackComponent->SetMobility(EComponentMobility::Movable);

}

void AOneHandedSwordCharacter::BeginPlay()
{
	Super::BeginPlay();

	attackComponent = Cast<UAttackComponent>(GetDefaultSubobjectByName(TEXT("AttackComponent")));
	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AOneHandedSwordCharacter::ActivateAttackComponent()
{
	Super::ActivateAttackComponent();
	attackComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AOneHandedSwordCharacter::DeactivateAttackComponent()
{
	Super::DeactivateAttackComponent();
	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}