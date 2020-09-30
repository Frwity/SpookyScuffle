// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM()
enum class E_TEAMS
{
	Ally,
	Enemy
};

/**
 * 
 */
class SPOOKYSCUFFLE_API ICharacterInterface
{
	GENERATED_BODY()

	
public:
	ICharacterInterface() {}


	virtual void ModifyLife(int _lifePoint, E_TEAMS _team) = 0;

	virtual int GetLife() = 0;

	virtual E_TEAMS GetTeam() = 0;

	virtual int GetDamage() = 0;
};
