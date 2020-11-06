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

void ABowmanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABowmanCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ABowmanCharacter::MoveForward(float _value)
{
	Super::MoveForward(_value);
}

void ABowmanCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void ABowmanCharacter::ModifyLife(int _lifePoint, E_TEAMS _team, bool _stun)
{
	Super::ModifyLife(_lifePoint, _team, _stun);
}


void ABowmanCharacter::Attack()
{
	Super::Attack();
	targetPos = Cast<AGeneralCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetActorLocation();
}