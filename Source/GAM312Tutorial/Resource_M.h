// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h" // Rendering text onto the object; testing purposes
#include "Components/StaticMeshComponent.h" // Allows us to define a static mesh for the Class
#include "Resource_M.generated.h"

UCLASS()
class GAM312TUTORIAL_API AResource_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///////////////////////////
	// Functions(Definitions) to handle resource collection and depletion; further elaborated in the c++ file.
	///////////////////////////
	UPROPERTY(EditAnywhere)
		FString resourceName = "Wood"; //Defaults to Wood; This value is passed to the Text Render(TEST).

	UPROPERTY(EditAnywhere)
		int resourceAmount = 5; //Defaults to 5, we get this on each res hit.

	UPROPERTY(EditAnywhere)
		int totalResource = 100; //Defaults to 100; the default total "health" of a resource before it is depleted.

	UPROPERTY()
		FText tempText;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* ResourceNameTxt;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;


};
