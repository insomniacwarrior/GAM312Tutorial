// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM312TUTORIAL_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	//These two essentially record the number of collections for the objective
	UFUNCTION(BlueprintImplementableEvent)
		void UpdatematObj(float matsCollected);
	
	UFUNCTION(BlueprintImplementableEvent)
		void UpdatebuildObj(float objectsBuilt);
};
