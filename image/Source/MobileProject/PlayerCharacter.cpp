// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();

	PlayerHealth = 3;
	Speed = 600.0f;
	Velocity = FVector(0.0f, 0.0f, 0.0f);
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	// PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
}

void APlayerCharacter::MoveX(float Value)
{
	Velocity.X = Value;
	Velocity.Y = 0;

	if (Value > 0)
	{
		SetActorRotation(FRotator(0, 0, 0));
	}
	else if (Value < 0)
	{
		SetActorRotation(FRotator(0, -180, 0));
	}
	AddMovementInput(Velocity);
}

void APlayerCharacter::MoveY(float Value)
{
	Velocity.X = 0;
	Velocity.Y = Value;

	if (Value > 0)
	{
		SetActorRotation(FRotator(0, 90, 0));
	}
	else if (Value < 0)
	{
		SetActorRotation(FRotator(0, -90, 0));
	}

	AddMovementInput(Velocity);
}
