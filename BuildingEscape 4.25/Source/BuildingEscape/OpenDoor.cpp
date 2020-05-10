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

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	

//	UE_LOG(LogTemp, Error, TEXT("SM_Door2, CloseAngle_SM_Door2 = {%f, %f, %f}"), CloseAngle.Pitch, CloseAngle.Roll, CloseAngle.Yaw);
	CloseAngle = Owner->GetActorRotation().Yaw;
	OpenAngle = CloseAngle;
	OpenAngle -= 90.f;

}

void UOpenDoor::OpenDoor()
{
	//UE_LOG(LogTemp, Error, TEXT("Owner->GetName() = %s"), Owner->GetName());

	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	// UE_LOG(LogTemp, Error, TEXT("DOOR CLOSED AT %f! Last Door open time was %f seconds ago, Delay = %f"), GetWorld()->GetTimeSeconds(), LastDoorOpenTime, DoorCloseDelay);
	Owner->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))  // Actor that opens is overlapping pressure plate
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();
}

