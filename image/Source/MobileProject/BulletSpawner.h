// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletSpawner.generated.h"

UCLASS()
class MOBILEPROJECT_API ABulletSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnCircularBulletPattern(TSubclassOf<AActor> BulletTypeA, TSubclassOf<AActor> BulletTypeB, int32 BulletCount, float Speed, bool bReverse);

	UFUNCTION(BlueprintCallable)
	void SpawnBulletAtDirection(TSubclassOf<AActor> BulletType, int32 BulletCount, float StartAngleRadians, float
	                            DeltaAngle, float Speed);

	UFUNCTION()
	void DelayedBulletSpawn(float Delay, int32 BulletCount, float Radius, float Speed);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BulletClassNormal;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BulletClassDestructible;

private:
	FTimerHandle BulletSpawnTimerHandle;
};
