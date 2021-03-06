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

	if (PressurePlate == nullptr)
		UE_LOG(LogTemp, Error, TEXT("%s missing component"), *Owner->GetName());

	CloseAngle = Owner->GetActorRotation().Yaw;
	OpenAngle = CloseAngle;
	OpenAngle = OpenAngle - 90.f;
}

//void UOpenDoor::CloseDoor()
//{
//	Owner->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
//}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float TotalMass = GetTotalMassOfActorsOnPlate();
	if (TotalMass >= TriggerMassThreshold)  // Actor that opens is overlapping pressure plate
	{
		//UE_LOG(LogTemp, Warning, TEXT("Total mass: %f"), TotalMass)
		OnOpen.Broadcast();
	}
	else
		OnClose.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<UPrimitiveComponent*> OverlappingComponents;
	if (PressurePlate == nullptr) { return TotalMass; }
	PressurePlate->GetOverlappingComponents(OUT OverlappingComponents);

	for (auto&& Component : OverlappingComponents)
		TotalMass += Component->GetMass();
	
	return TotalMass;
}

