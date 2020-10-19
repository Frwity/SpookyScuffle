// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "AreaDamage.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYSCUFFLE_API UAreaDamage : public UBoxComponent
{
	GENERATED_BODY()


		virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Option, meta = (AllowPrivateAccess = "true"))
		int damageTaken = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Option, meta = (AllowPrivateAccess = "true"))
		float coolDown = 0.4;

	bool stopTimer = false;
	float saveCoolDown;
	FTimerHandle outHandleTimer;
	class AGeneralCharacter* saveCharacter;

public:
	UAreaDamage();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void TakeDamage();

};
