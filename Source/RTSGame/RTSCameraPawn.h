// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

UCLASS()
class RTSGAME_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()
		
	/** Camera Component */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* CameraComponent;

	/** Camera Movement Speed */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraMovementSpeed;

	/** Camera Movement Threshold */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraMovementThreshold;

	/** Camera Left and Right axis value */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraLeftRightAxisValue;

	/* Camera Zoom Axis Value */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraZoomAxisValue;

	/** Camera Up and Down axis value */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraUpDownAxisValue;

	/* Camera Zoom Speed*/
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraZoomSpeed;

	/* Camera Zoom min - max distance */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	float MinCameraZoomDistance;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	float MaxCameraZoomDistance;

public:
	// Sets default values for this pawn's properties
	ARTSCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera Movement and Zoom
	void ZoomCamera(float Value);
	void MoveCameraLeftRight(float Value);
	void MoveCameraUpDown(float Value);
};
