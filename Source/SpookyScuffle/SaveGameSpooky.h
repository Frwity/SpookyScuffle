// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameSpooky.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API USaveGameSpooky : public USaveGame
{
	GENERATED_BODY()

protected:

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString playerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString saveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 userIndex;

public:

    USaveGameSpooky();
    USaveGameSpooky(FString namePlayer, FString nameSlot, int index);
	
    void SaveGame();
    UFUNCTION(BlueprintCallable)
        void SaveGame(FString namePlayer,FString nameSlot,int index);

    void LoadGame();

    UFUNCTION(BlueprintCallable)
        void LoadGame(FString nameSlot, int index);

    void SetSavedGame(FString namePlayer, FString nameSlot, int index);
    void mySaveGame();
    
};
