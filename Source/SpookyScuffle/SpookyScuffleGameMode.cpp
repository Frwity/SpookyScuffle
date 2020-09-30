// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpookyScuffleGameMode.h"
#include "SpookyScuffleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpookyScuffleGameMode::ASpookyScuffleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
