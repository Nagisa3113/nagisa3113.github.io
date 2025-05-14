// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);

	ControlledEnemy = Cast<AEnemyCharacter>(PawnToPossess);
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequsetID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequsetID, Result);
	// GoToRandomDestination();
}

void AEnemyAIController::GoToRandomDestination()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);
	if (NavMesh)
	{
		const float SearchRadius = 10000.0f;
		FNavLocation RandomLocation;
		const bool bNewDestinationFound = NavMesh->GetRandomReachablePointInRadius(
			ControlledEnemy->GetActorLocation(), SearchRadius, RandomLocation);
		if (bNewDestinationFound)
		{
			MoveToLocation(RandomLocation.Location, 50.0f);
		}
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
	
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}
