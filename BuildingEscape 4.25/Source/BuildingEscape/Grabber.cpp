// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "BuildingEscape.h"
#include "DrawDebugHelpers.h"
#define OUT 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	/*UE_LOG(LogTemp, Warning, TEXT("PLAYER VIEWPOINT: %s, LOCATION: %s"), 
		*PlayerViewPointRotation.ToString(), 
		*PlayerViewPointLocation.ToString()
	)*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
	// draw a red trace in the world to visualise
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	// ray-cast out to certain distance
	// see what we hit
}

