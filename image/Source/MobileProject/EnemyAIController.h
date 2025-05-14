// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	void OnPossess(class APawn* PawnToPossess) override;

	virtual void OnMoveCompleted(FAIRequestID RequsetID, const FPathFollowingResult& Result) override;

	void GoToRandomDestination();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;


	virtual void BeginPlay() override;

private:
	class AEnemyCharacter* ControlledEnemy;
};
