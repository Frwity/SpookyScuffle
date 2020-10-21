// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class SPOOKYSCUFFLE_API AArrow : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Characteristic, meta = (AllowPrivateAccess = "true"))
		FVector direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Characteristic, meta = (AllowPrivateAccess = "true"))
		E_TEAMS team;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Characteristic, meta = (AllowPrivateAccess = "true"))
		float damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Characteristic, meta = (AllowPrivateAccess = "true"))
		float speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Characteristic, meta = (AllowPrivateAccess = "true"))
		float lifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* arrowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* hitBox;
	
	virtual void BeginPlay() override;

public:	
	
	AArrow();
	AArrow(FVector _direction, E_TEAMS _team);

    void DestroyArrow();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
