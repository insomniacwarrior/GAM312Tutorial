// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Creates a camera component
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));
	// Takes the created camera, attaches it to where the head bone is one the character mesh
	PlayerCamComp->SetupAttachment(GetMesh(), "head");
	// Sets the camera to use the pawn's control rotation
	PlayerCamComp->bUsePawnControlRotation = true;
	// Establishes the size of ResourcesArray, adds the names of the resources after.
	ResourcesArray.SetNum(3);
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));


}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	// Sets a timer to call the DecreaseStats function every 2 seconds
	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreaseStats, 2.0f, true);

	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Binds the input axis and actions to the respective functions
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump);
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject);
}

void APlayerChar::MoveForward(float axisValue)
{
	// Gets the forward direction of the player based on the control rotation and adds movement input in that direction
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::MoveRight(float axisValue)
{
	// Gets the right direction of the player based on the control rotation and adds movement input in that direction
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::StartJump()
{
	// Simple jump bool
	bPressedJump = true;
}

void APlayerChar::StopJump()
{
	// SImple jump bool
	bPressedJump = false;
}

///////////////////////////
// This function serves as a RayCast, enabling Player Interactions via a left click.
///////////////////////////
void APlayerChar::FindObject()
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f; // 800 units front of camera pos
	FVector EndLocation = StartLocation + Direction;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); //Ignores self when casting
	QueryParams.bTraceComplex = true; //Traces Complex Objects(Collision)
	QueryParams.bReturnFaceIndex = true; //Returns the index of the face of the object hit

	// This bit here is where the cast is performed, and returns the relevant information to the HitResult.
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor()); //Sets variable to HitResource if ray hits an actual resource

		if (Stamina > 5.0f) //Checks if stamina is there to consume first
		{
			if (HitResource)
			{
				FString hitName = HitResource->resourceName; //Gets the name of the resource hit
				int resourceValue = HitResource->resourceAmount; //Gets the amount of the resource obtained

				HitResource->totalResource = HitResource->totalResource - resourceValue; //Decreases the total "health" of the hit resource.

				// If the resource has "health" remaining, collect it. Otherwise, Destroy it.
				if (HitResource->totalResource > resourceValue)
				{
					GiveResource(resourceValue, hitName);

					check(GEngine != nullptr); //Ensures the engine's subsystem can display the text before firing.
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected!"));
					// Decal goes splat
					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f,10.0f,10.0f), HitResult.Location, FRotator(-90, 0,0), 2.0f);
					
					SetStamina(-5.0f); //Consumes the stamina
				}
				else
				{
					HitResource->Destroy();
					check(GEngine != nullptr); //Ensures the engine's subsystem can display the text before firing.
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted!"));	
				}
			}
		}
		
	}
}

///////////////////////////
// These functions determine the mechanic for ADDING TO the player's stats.
///////////////////////////

void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100)
	{
		Health = Health + amount;

	}
}

void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100)
	{
		Hunger = Hunger + amount;

	}
}

void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount < 100)
	{
		Stamina = Stamina + amount;

	}
}

///////////////////////////
// This function will essentially trade hunger to regenerate stamina on each iteration.
// If the player has no more hunger, this instead eats into their remaining health.
///////////////////////////

void APlayerChar::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}
	
	SetStamina(10.0f);

	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}
}

///////////////////////////
// This function will add the amount of resources obtained to the player's ResourcesArray, 
// based on the Resource Type passed by the RayCast.
///////////////////////////

void APlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}
	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}
	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
}