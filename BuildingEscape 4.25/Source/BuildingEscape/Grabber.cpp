// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "BuildingEscape.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
=======
>>>>>>> parent of 68c2c09... Committed StarterContent and .vs directory
=======
>>>>>>> ba2d1b58b4542f01df2a6bbb6589e79af7dd9746
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
	
	/// look for attached physics handle
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	UE_LOG(LogTemp, Warning, TEXT("PLAYER VIEWPOINT: %s, LOCATION: %s"), 
		*PlayerViewPointRotation.ToString(), 
		*PlayerViewPointLocation.ToString()
<<<<<<< HEAD
<<<<<<< HEAD
	)*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
	/// draw a red trace in the world to visualise
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

	/// setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// line-trace (AKA ray-cast) out to certain distance
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("OBJECT HIT: %s"), *(ActorHit->GetName()))
	}
=======
	)
>>>>>>> parent of 68c2c09... Committed StarterContent and .vs directory
=======
	)
>>>>>>> ba2d1b58b4542f01df2a6bbb6589e79af7dd9746
}

