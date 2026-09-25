// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AUContrTut.generated.h"

/**
 * 
 */
UCLASS()
class GAM312TUTORIAL_API AAUContrTut : public AAIController
{
	GENERATED_BODY()
	
public:
	AAUContrTut();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
