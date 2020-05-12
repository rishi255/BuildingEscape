// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "BuildingEscape.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

#define OUT 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NO PHYSICS HANDLE COMPONENT FOUND for %s"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInput)
	{
		PawnInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("INPUT COMPONENT NOT FOUND for %s"), *GetOwner()->GetName())
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();	// gets the mesh in our case

	// if we hit something then attach a physics handle
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,	// no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetRelativeRotation()
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grab released!!"))
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if physics handle is not attached, return
	if (!PhysicsHandle) { return; }
	
	// move the object that we're holding to the line trace end.
	auto LineTracePoints = GetLineTracePoints();
	PhysicsHandle->SetTargetLocation(GetLineTracePoints().v2);
}

FTwoVectors UGrabber::GetLineTracePoints()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, // also LineTraceStart, the starting point of the line trace 
		OUT PlayerViewPointRotation
	);
	/// set line trace end by getting viewpoint location and rotation
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	return FTwoVectors(PlayerViewPointLocation, LineTraceEnd);
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult HitResult;
	auto LineTracePoints = GetLineTracePoints();

	/// setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// line-trace (AKA ray-cast) out to certain distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		LineTracePoints.v1,
		LineTracePoints.v2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// see if we actually hit something and then return the FHitResult object.
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit - %s!"), *(ActorHit->GetName()));
	}

	return HitResult;
}