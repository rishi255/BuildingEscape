// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Classes/Components/ActorComponent.h"
#include"GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	CloseAngle = Owner->GetActorRotation().Yaw;
	OpenAngle = CloseAngle;
	OpenAngle = OpenAngle - 90.f;
}

void UOpenDoor::OpenDoor()
{

	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float TotalMass = GetTotalMassOfActorsOnPlate();
	if (TotalMass >= TriggerMassThreshold)  // Actor that opens is overlapping pressure plate
	{
		UE_LOG(LogTemp, Warning, TEXT("Total mass: %f"), TotalMass)
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	PressurePlate->GetOverlappingComponents(OUT OverlappingComponents);
	float TotalMass = 0.f;

	for (auto&& Component : OverlappingComponents)
		TotalMass += Component->GetMass();
	
	return TotalMass;
}

