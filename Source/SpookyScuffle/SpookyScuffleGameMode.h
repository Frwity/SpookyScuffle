// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpookyScuffleGameMode.generated.h"


UCLASS(minimalapi)
class ASpookyScuffleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class AEnemyAIManager* enemyAIManager;

	virtual void BeginPlay() override;

public:
	ASpookyScuffleGameMode();
};



