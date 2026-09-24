// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "AICharTut.generated.h"

UCLASS()
class GAM312TUTORIAL_API AAICharTut : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharTut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* BTree;
	
	UBehaviorTree* GetBehaviorTree() const;

};
