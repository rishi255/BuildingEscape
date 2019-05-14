// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
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

	FRotator Rot, NewRot = { 0, 30, 0 };
	AActor *Owner;
	Owner = GetOwner();
	Rot = Owner->GetActorRotation();

	FString OwnerRotation = Rot.ToString();
	FString NewRotation = NewRot.ToString();
	UE_LOG(LogTemp, Error, TEXT("Owner %s has rotation %s"), *Owner->GetName(), *OwnerRotation)
	
	if(Owner->SetActorRotation(NewRot) == 1)
		UE_LOG(LogTemp, Error, TEXT("Rotation set to %s"), *NewRotation)
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

