// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "BobAIController.generated.h"

/**
 * 
 */
UCLASS()
class ZWENTENDORF_API ABobAIController : public AAIController
{
	GENERATED_BODY()
	
	/*Behavior tree comp ref*/
	UBehaviorTreeComponent* BehaviorComp;

	/*----------Blackboard----------*/

	/*Blackboard comp ref*/
	UBlackboardComponent* BlackboardComp;

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	/*----------Blackboard----------*/

	/*I use the AActor class as the Template class so I can use the GetAllActorsOfClass function.
	However, in this collection I'm going to store all the Available ABotTargetPoint instances.*/
	TArray<AActor*> BotTargetPoints;

	/*Posses is executed when the character we want to control is spawned.
	Inside this function, we initialize the blackboard and start the behavior tree*/
	virtual void Possess(APawn* Pawn) override;

public:
	ABobAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return BotTargetPoints; }
};
