// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include"Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"
#define FROTATOR_ORDER Y,Z,X // PITCH, YAW, ROLL

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:

	UPROPERTY(VisibleAnywhere)
	float OpenAngle;
	UPROPERTY(VisibleAnywhere)
	float CloseAngle;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	// total mass of all actors falling inside the trigger should be at least this value to trigger it
		float TriggerMassThreshold = 25.f;	

	float GetTotalMassOfActorsOnPlate();
	AActor* Owner = nullptr;
};
