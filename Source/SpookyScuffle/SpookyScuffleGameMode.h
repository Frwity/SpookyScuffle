// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpookyScuffleGameMode.generated.h"

UENUM()
enum class E_GAMESTATE
{
	STARTING,
	PAUSE,
	WIN,
	GAMEOVER,
	QUIT
};

UCLASS(minimalapi)
class ASpookyScuffleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	E_GAMESTATE state;

public:
	ASpookyScuffleGameMode();
};



