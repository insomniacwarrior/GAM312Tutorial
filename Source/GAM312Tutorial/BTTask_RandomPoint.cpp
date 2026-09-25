// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomPoint.h"
#include "NavigationSystem.h"
#include "AUContrTut.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RandomPoint::UBTTask_RandomPoint(FObjectInitializer const& ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_RandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const contr = Cast<AAUContrTut>(OwnerComp.GetAIOwner()))
	{
		if (APawn* const aic = contr->GetPawn())
		{
			auto const Origin = aic->GetActorLocation();
			
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
