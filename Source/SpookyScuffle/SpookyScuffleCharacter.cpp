// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpookyScuffleCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"	
#include "Animation/AnimTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"


ASpookyScuffleCharacter::ASpookyScuffleCharacter()
	: ATwoHandedSwordCharacter{}
{
	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f;
	cameraBoom->bUsePawnControlRotation = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

}

void ASpookyScuffleCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASpookyScuffleCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ASpookyScuffleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASpookyScuffleCharacter::Attack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateDash);
	PlayerInputComponent->BindAction("Lock", IE_Pressed, this, &ASpookyScuffleCharacter::ActivateLock);
	PlayerInputComponent->BindAction("Lock", IE_Released, this, &ASpookyScuffleCharacter::DisableLock);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpookyScuffleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpookyScuffleCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpookyScuffleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpookyScuffleCharacter::LookUpAtRate);
	
}

void ASpookyScuffleCharacter::TurnAtRate(float _rate)
{
	AddControllerYawInput(_rate * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASpookyScuffleCharacter::LookUpAtRate(float _rate)
{
	AddControllerPitchInput(_rate * baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASpookyScuffleCharacter::MoveForward(float _value)
{
	Super::MoveForward(_value);
}

void ASpookyScuffleCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void ASpookyScuffleCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	Super::ModifyLife(_lifePoint, _team);
}

void ASpookyScuffleCharacter::Attack()
{
	Super::Attack();
}

void ASpookyScuffleCharacter::ActivateDash()
{
	if (!isDash)
	{
		isDash = true;
		savePosDash = GetActorLocation();
		GetWorldTimerManager().SetTimer(outHandleDash, this, &ASpookyScuffleCharacter::DashMovement, GetWorld()->GetDeltaSeconds(), true);
	}
}

void ASpookyScuffleCharacter::DashMovement()
{
	if (!isCoolDownDash)
	{
		// Movement Of Dash
		timerDash += GetWorld()->DeltaTimeSeconds;
		
		if ((savePosDash - GetActorLocation()).Size() < distanceDash)
		{
			GetCharacterMovement()->Velocity = GetActorForwardVector() * speedDash * 10;
			GetCharacterMovement()->MaxAcceleration = speedDash * 10;
		}
		if (timerDash > distanceDash / 1000.f || (savePosDash - GetActorLocation()).Size() >= distanceDash)
		{
			isCoolDownDash = true;
			timerDash = 0;
			GetCharacterMovement()->MaxAcceleration = 2048; // default value 
			GetCharacterMovement()->Velocity = GetActorForwardVector() * 0;
		}
	}
	else
	{
		// CoolDown Of Dash
		timerCoolDownDash += GetWorld()->DeltaTimeSeconds;
	
		if (timerCoolDownDash > coolDownDash)
		{
			isCoolDownDash = false;
			timerCoolDownDash = 0.f;
			isDash = false;
			GetWorldTimerManager().ClearTimer(outHandleDash);
		}
	}
}

void ASpookyScuffleCharacter::ActivateLock()
{
	if (!loadLock)
	{
		loadLock = true;

		TArray<AActor*> enemiesTwoHanded;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATwoHandedSwordCharacter::StaticClass(), enemiesTwoHanded);

		angleLock = 60;

		for (AActor* enemOfList : enemiesTwoHanded)
		{
			ATwoHandedSwordCharacter* enemy = Cast<ATwoHandedSwordCharacter>(enemOfList);

			if (enemy != nullptr && enemy != this)
			{
				
				if (CheckEnemyToLock(enemy->GetActorLocation(), GetActorLocation()))
					enemyToLock = enemy;
			
			}

		}

	}

	// we find enemy 

	if (enemyToLock != nullptr)
	{
		enemyToLock->Jump();
	}


}

bool ASpookyScuffleCharacter::CheckEnemyToLock(FVector enemy, FVector posPlayer)
{

		if ((enemy - posPlayer).Size() < distanceMaxLock)
		{
			FVector _forwardVec = { GetActorForwardVector().X,GetActorForwardVector().Y, 0};
			FVector _playerToEnemy = { (enemy - posPlayer).X, (enemy - posPlayer).Y, 0 };

			float  _calcAngle = FVector::DotProduct(_forwardVec.GetSafeNormal(), _playerToEnemy.GetSafeNormal());
			float _newAngle = (acosf(_calcAngle)) * 180 / PI;


			if (_newAngle < angleLock)
			{
				angleLock = _newAngle;
				return true;
			}
		}
		else
		{
			return false;
		}

		return false;
	
}

void ASpookyScuffleCharacter::DisableLock()
{
	if (enemyToLock != nullptr)
	{
		enemyToLock->StopJumping() ;
		enemyToLock = nullptr;
	}
	
	loadLock = false;
}