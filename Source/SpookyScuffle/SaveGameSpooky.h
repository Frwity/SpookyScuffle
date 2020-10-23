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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic, meta = (AllowPrivateAccess = "true"))
        FString playerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic, meta = (AllowPrivateAccess = "true"))
        FString saveSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic, meta = (AllowPrivateAccess = "true"))
        int userIndex;

    TArray<FTransform> transformCharacter ;
    TArray<int> indexCharacter;
    TArray<bool> isAliveCharacter;

    int indexMax;



public:

    USaveGameSpooky();
    USaveGameSpooky(FString namePlayer, FString nameSlot, int index);


    UFUNCTION(BlueprintCallable)
        void LoadGame(FString nameSlot, int index);

    void SetSavedGame(FString namePlayer, FString nameSlot, int index);
    void mySaveGame();
    class ACheckPoint* myCheckPoint;
    
};
