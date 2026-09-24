// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharTut.h"

// Sets default values
AAICharTut::AAICharTut()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharTut::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharTut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharTut::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* AAICharTut::GetBehaviorTree() const
{
	return BTree;
}

