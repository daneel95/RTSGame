// Fill out your copyright notice in the Description page of Project Settings.

// My game includes
#include "RTSCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "RTSController.h"

// Engine Includes
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

// Sets default values
ARTSCameraPawn::ARTSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Camera Values
	CameraMovementThreshold = 5.0f;
	CameraMovementSpeed = 5000.0f;
	MinCameraZoomDistance = 500.0f;
	MaxCameraZoomDistance = 2500.0f;
	CameraZoomSpeed = 10000.0f;

	// Initialize Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RTSCamera"));
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 1500.0f));
	CameraComponent->SetRelativeRotation(FRotator(300.0f, 0.0f, 0.0f));
	CameraComponent->AttachTo(RootComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Get mouse input
	float MouseX;
	float MouseY;
	
	// Get viewport size
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	// Calculate borders
	const float ScrollBorderRight = ViewportSize.X - CameraMovementThreshold;
	const float ScrollBorderTop = ViewportSize.Y - CameraMovementThreshold;

	// Get mouse position and change camera movement values accordingly
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY)) {
		// Handle left right axis value
		if (MouseX <= CameraMovementThreshold) {
			CameraLeftRightAxisValue += (MouseX / CameraMovementThreshold) - 1;
		}
		else if (MouseX >= ScrollBorderRight) {
			CameraLeftRightAxisValue += (MouseX - ScrollBorderRight) / CameraMovementThreshold;
		}

		// Handle up down axis value
		if (MouseY <= CameraMovementThreshold) {
			CameraUpDownAxisValue += 1 - (MouseY / CameraMovementThreshold);
		}
		else if (MouseY >= ScrollBorderTop) {
			CameraUpDownAxisValue -= (MouseY - ScrollBorderTop) / CameraMovementThreshold;
		}
	}

	// Apply input
	CameraLeftRightAxisValue = FMath::Clamp(CameraLeftRightAxisValue, -1.0f, 1.0f);
	CameraUpDownAxisValue = FMath::Clamp(CameraUpDownAxisValue, -1.0f, 1.0f);

	FVector ActorLocation = this->GetActorLocation();
	FVector RightVectorValue = FVector::RightVector * CameraMovementSpeed * CameraLeftRightAxisValue * DeltaTime;
	FVector ForwardVectorValue = FVector::ForwardVector * CameraMovementSpeed * CameraUpDownAxisValue * DeltaTime;
	ActorLocation += RightVectorValue;
	ActorLocation += ForwardVectorValue;
	FVector2D CameraOffsetForController(RightVectorValue.Y, ForwardVectorValue.X);
	Cast<ARTSController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->AddToCameraMovementOffset(CameraOffsetForController);
	
	SetActorLocation(ActorLocation);

	FVector CameraLocation = CameraComponent->RelativeLocation;
	CameraLocation.Z += CameraZoomSpeed * CameraZoomAxisValue * DeltaTime;
	CameraLocation.Z = FMath::Clamp(CameraLocation.Z, MinCameraZoomDistance, MaxCameraZoomDistance);
	CameraComponent->SetRelativeLocation(CameraLocation);
}

// Called to bind functionality to input
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("MoveCameraLeftRight"), this, &ARTSCameraPawn::MoveCameraLeftRight);
	InputComponent->BindAxis(TEXT("MoveCameraUpDown"), this, &ARTSCameraPawn::MoveCameraUpDown);
	InputComponent->BindAxis(TEXT("ZoomCamera"), this, &ARTSCameraPawn::ZoomCamera);
}

void ARTSCameraPawn::ZoomCamera(float Value) {
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	CameraZoomAxisValue = Value;
}

void ARTSCameraPawn::MoveCameraLeftRight(float Value) {
	CameraLeftRightAxisValue = Value;
}

void ARTSCameraPawn::MoveCameraUpDown(float Value) {
	CameraUpDownAxisValue = Value;
}
