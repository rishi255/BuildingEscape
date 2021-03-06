// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
		FVector PlayerViewPointLocation = FVector(0, 0, 0);
	UPROPERTY(VisibleAnywhere)
		FRotator PlayerViewPointRotation = FRotator(0, 0, 0);

	// how far ahead of the player we can reach (in cms)
	UPROPERTY(EditAnywhere)
		float Reach = 120.f;

	UPROPERTY(VisibleAnywhere)
		UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY(VisibleAnywhere)
		UInputComponent* PawnInput = nullptr;

	void Grab();
	void Release();

	// find UPhysicsHandleComponent, then do stuff
	void FindPhysicsHandle();

	// find UInputComponent and then bind actions (grab and release)
	void SetupInputComponent();

	// return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// gets start and end vectors of the line trace and returns them as a pair
	FTwoVectors GetLineTracePoints();
};
