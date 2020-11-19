// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "Perception/PawnSensingComponent.h"

AArcherCharacter::AArcherCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
}