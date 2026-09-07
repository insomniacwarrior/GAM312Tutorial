// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAM312TUTORIAL_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///////////////////////////
	// Functions(Definitions) to handle player movement and actions; further elaborated in the c++ file.
	///////////////////////////

	UFUNCTION()
		void MoveForward(float axisValue);

	UFUNCTION()
		void MoveRight(float axisValue);

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void FindObject();

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamComp;
	
	///////////////////////////
	// Properties to hold the player's stats. 
	// 
	// UPROPERTY establishes a variable.
	// EditAnywhere allows the variable to be edited(grants visibility) within the Class.
	// BlueprintReadWrite allows the variable to be read and written to within the Blueprint(GUI).
	// The Category is used to group the variable(s) within the Class(Details Panel Dropdown!).
	///////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Hunger = 100.0f;

	///////////////////////////
	// Functions that define the behavior of the player's stats. Defined within the C++ file.
	///////////////////////////

	UFUNCTION(BlueprintCallable)
		void SetHealth(float amount);
	
	UFUNCTION(BlueprintCallable)
		void SetHunger(float amount);

	UFUNCTION(BlueprintCallable)
		void SetStamina(float amount);
		
	UFUNCTION()
		void DecreaseStats();

};
