// Fill out your copyright notice in the Description page of Project Settings.


#include "AUContrTut.h"
#include "AICharTut.h"
#include "BehaviorTree/BlackboardComponent.h"

AAUContrTut::AAUContrTut()
{
}

void AAUContrTut::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (AAICharTut* const aic = Cast<AAICharTut>(InPawn))
	{
		if (UBehaviorTree* const tree = aic->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
