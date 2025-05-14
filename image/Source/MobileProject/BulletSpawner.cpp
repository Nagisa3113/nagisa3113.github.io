// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletSpawner.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletSpawner::ABulletSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABulletSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABulletSpawner::SpawnCircularBulletPattern(TSubclassOf<AActor> BulletTypeA, TSubclassOf<AActor> BulletTypeB,
                                                int32 BulletCount, float Speed, bool bReverse)
{
	FVector SpawnLocation = GetActorLocation();
	float AngleStep = 360.0f / BulletCount;
	TSubclassOf<AActor> BulletType = BulletTypeA;
	for (int32 i = 0; i < BulletCount; ++i)
	{
		float AngleInRadians = FMath::DegreesToRadians(i * AngleStep);
		FVector Direction = FVector(FMath::Cos(AngleInRadians), FMath::Sin(AngleInRadians), 0.0f);
		if (bReverse)
		{
			if (BulletType == BulletTypeA)
			{
				BulletType = BulletTypeB;
			}
			else
			{
				BulletType = BulletTypeA;
			}
		}
		if (BulletType)
		{
			AActor* Bullet = GetWorld()->SpawnActor<AActor>(BulletType, SpawnLocation, FRotator::ZeroRotator);
			UProjectileMovementComponent* ProjectileMovement =
				Cast<UProjectileMovementComponent>(
					Bullet->GetComponentByClass(UProjectileMovementComponent::StaticClass()));
			if (ProjectileMovement)
			{
				ProjectileMovement->Velocity = Direction * Speed;
			}
		}
	}
}

void ABulletSpawner::SpawnBulletAtDirection(TSubclassOf<AActor> BulletType, int32 BulletCount, float StartAngleRadians,
                                            float DeltaAngle, float Speed)
{
	FVector SpawnLocation = GetActorLocation();

	for (int32 i = 0; i < BulletCount; ++i)
	{
		float AngleInRadians = FMath::DegreesToRadians(DeltaAngle);
		float StartAngleInRadians= FMath::DegreesToRadians(StartAngleRadians);

		FVector Direction;
		Direction += FVector(FMath::Cos(AngleInRadians + StartAngleInRadians),
		                     FMath::Sin(AngleInRadians + StartAngleInRadians), 0.0f);
		Direction.Normalize();

		if (BulletType)
		{
			AActor* Bullet = GetWorld()->SpawnActor<AActor>(BulletType, SpawnLocation, FRotator::ZeroRotator);
			UProjectileMovementComponent* ProjectileMovement =
				Cast<UProjectileMovementComponent>(
					Bullet->GetComponentByClass(UProjectileMovementComponent::StaticClass()));
			if (ProjectileMovement)
			{
				ProjectileMovement->Velocity = Direction * Speed;
			}
		}
	}
}

void ABulletSpawner::DelayedBulletSpawn(float Delay, int32 BulletCount, float Radius, float Speed)
{
	// GetWorld()->GetTimerManager().SetTimer(BulletSpawnTimerHandle,
	//                                        [this, BulletCount, Radius, Speed]()
	//                                        {
	// 	                                       SpawnCircularBulletPattern(TODO, BulletCount, Speed);
	//                                        }, Delay, false);
}
