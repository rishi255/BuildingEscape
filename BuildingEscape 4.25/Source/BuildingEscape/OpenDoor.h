// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
//	UPROPERTY(VisibleAnywhere)
//		FRotator OpenAngle;  //  for door 2 -> FRotator(0.f, 0.f, 0.f);
//	UPROPERTY(VisibleAnywhere)
//		FRotator CloseAngle; //  for door 2 -> FRotator(0.f, 0.f, 90.f)

//	UPROPERTY(VisibleAnywhere)
//		FRotator OpenAngle_SM_Door3 = FRotator(0.f, 0.f, 90.f);
//	UPROPERTY(VisibleAnywhere)
//		FRotator CloseAngle_SM_Door3 = FRotator(0.f, 0.f, 180.f);
	
	UPROPERTY(VisibleAnywhere)
	float OpenAngle;
	UPROPERTY(VisibleAnywhere)
	float CloseAngle;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;

	AActor* ActorThatOpens;
	// remember pawn inherits from actor

	AActor* Owner;
};
