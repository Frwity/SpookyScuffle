// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralCharacter.h"
#include "HandFreeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API AHandFreeCharacter : public AGeneralCharacter
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

	virtual void MoveForward(float _value) override;
	virtual void MoveRight(float _value) override;

public:
	AHandFreeCharacter();

	virtual void ModifyLife(int _lifePoint, E_TEAMS _team) override;

};