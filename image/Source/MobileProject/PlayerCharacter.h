// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MOBILEPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// UStaticMeshComponent* PlayerDisplayMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float Value);
	void MoveY(float Value);

private:
	FVector StartLocation;
	FVector Velocity;
	FTimerHandle TimerHandle;
};
