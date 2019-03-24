// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSController.h"
#include "UnitActor.h"
#include "RTSAICharacterController.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"


ARTSController::ARTSController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;
}

void ARTSController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Select"), IE_Pressed, this, &ARTSController::StartSelecting);
	InputComponent->BindAction(TEXT("Select"), IE_Released, this, &ARTSController::StopSelecting);
	InputComponent->BindAction(TEXT("RightMouseClick"), IE_Pressed, this, &ARTSController::HandleRightMouseClick);
}

void ARTSController::StartSelecting() {
	float MouseX;
	float MouseY;

	FHitResult Hit;
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit)) {
		return;
	}

	PrintOnScreen("START SELECTION -- " + Hit.Location.ToString());

	if (GetMousePosition(MouseX, MouseY)) {
		SelectionFrameScreenStartPosition = FVector2D(MouseX, MouseY);
		CameraMovementOffset = FVector2D(0.0f, 0.0f);
		SelectionFrameWorldStartPosition = Hit.Location;
		bCreatingSelectionFrame = true;
	}
}

void ARTSController::StopSelecting() {
	PrintOnScreen("STOP SELECTIONS!");

	FIntRect WorldSelectionFrame;
	if (!GetSelectionFrameWorld(WorldSelectionFrame)) {
		bCreatingSelectionFrame = false;
		return;
	}

	GetAllActorsInSelectionFrame(WorldSelectionFrame, CurrentlySelectedActors);
	bCreatingSelectionFrame = false;
}

void ARTSController::GetAllActorsInSelectionFrame(FIntRect SelectionFrame, TArray<AActor*>& FinalSelectedActors) {
	// Handle actors that will be deselected
	for (AActor* SelectedActor : CurrentlySelectedActors) {
		HandleDeselectedActor(SelectedActor);
	}
	// Empty the selection array
	FinalSelectedActors.Empty();

	// TODO: If the selection area is really small consider it a click
	if (SelectionFrame.Area() < 10) {
		// Consider it a click
		TArray<AActor*> SingleSelectedActor;
		GetActorOnClick(FinalSelectedActors);
		return;
	}
	// Iterate through all the actors and return the selected ones
	// TODO: Get just player owned actors - maybe a tag on them - after I get all player stuff done
	for (TActorIterator<AActor> SActor(GetWorld()); SActor; ++SActor) {
		AActor* SelectedActor = *SActor;
		FVector ActorLocation = SelectedActor->GetActorLocation();
		if (SelectionFrame.Contains(FIntPoint(ActorLocation.X, ActorLocation.Y))) {
			HandleSelectedActor(SelectedActor, FinalSelectedActors);
		}
	}
}

void ARTSController::GetActorOnClick(TArray<AActor*>& FinalSelectedActors) {
	FHitResult Hit;
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit)) {
		return;
	}

	HandleSelectedActor(Hit.GetActor(), FinalSelectedActors);
}

void ARTSController::HandleSelectedActor(AActor* SelectedActor, TArray<AActor*>& FinalSelectedActors) {
	// Handle different actors differently
	// TODO: check for owner
	if (SelectedActor->IsA(AUnitActor::StaticClass())) {
		AUnitActor* Unit = Cast<AUnitActor>(SelectedActor);
		Unit->SetSelectionIndicatorVisibility(true);
	}
	else {
		return;
	}

	// Add that actor to selected actors list
	FinalSelectedActors.Add(SelectedActor);
}

void ARTSController::HandleDeselectedActor(AActor* DeselectedActor) {
	if (DeselectedActor->IsA(AUnitActor::StaticClass())) {
		AUnitActor* Unit = Cast<AUnitActor>(DeselectedActor);
		Unit->SetSelectionIndicatorVisibility(false);
	}
}

bool ARTSController::GetSelectionFrameWorld(FIntRect& OutSelectionFrame) {
	if (!bCreatingSelectionFrame) {
		return false;
	}

	FHitResult Hit;
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit)) {
		return false;
	}
	
	PrintOnScreen("END HIT LOCATION -- " + Hit.Location.ToString());

	// Get the created rectangle and place it in OutSelectionFrame - create the frame itself
	float MinX = FMath::Min(SelectionFrameWorldStartPosition.X, Hit.Location.X);
	float MaxX = FMath::Max(SelectionFrameWorldStartPosition.X, Hit.Location.X);
	float MinY = FMath::Min(SelectionFrameWorldStartPosition.Y, Hit.Location.Y);
	float MaxY = FMath::Max(SelectionFrameWorldStartPosition.Y, Hit.Location.Y);

	OutSelectionFrame = FIntRect(FIntPoint(MinX, MinY), FIntPoint(MaxX, MaxY));
	return true;
}

bool ARTSController::GetSelectionFrame(FIntRect& OutSelectionFrame) {
	if (!bCreatingSelectionFrame) {
		return false;
	}

	float MouseX;
	float MouseY;

	if (!GetMousePosition(MouseX, MouseY)) {
		return false;
	}
	

	// Get the created rectangle and place it in OutSelectionFrame - create the frame itself
	float MinX = FMath::Min(SelectionFrameScreenStartPosition.X - CameraMovementOffset.X, MouseX);
	float MaxX = FMath::Max(SelectionFrameScreenStartPosition.X - CameraMovementOffset.X, MouseX);
	float MinY = FMath::Min(SelectionFrameScreenStartPosition.Y + CameraMovementOffset.Y, MouseY);
	float MaxY = FMath::Max(SelectionFrameScreenStartPosition.Y + CameraMovementOffset.Y, MouseY);

	OutSelectionFrame = FIntRect(FIntPoint(MinX, MinY), FIntPoint(MaxX, MaxY));
	return true;
}

void ARTSController::HandleRightMouseClick() {
	PrintOnScreen("Right clicked!!");
	// if nothing is selected do nothing
	if (CurrentlySelectedActors.Num() <= 0) {
		return;
	}

	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	// For now just assume all you selected are units
	// TODO: Handle different selection differently
	for (AActor* SelectedActor : CurrentlySelectedActors) {
		if (SelectedActor->IsA(AUnitActor::StaticClass())) {
			PrintOnScreen("Starting to handle stuff");
			AUnitActor* Unit = Cast<AUnitActor>(SelectedActor);
			Unit->MoveUnitToLocation(Hit.Location);
		}
	}
}

void ARTSController::AddToCameraMovementOffset(FVector2D OffsetToAdd) {
	CameraMovementOffset += OffsetToAdd;
}

void ARTSController::PrintOnScreen(FString Text) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Text);
}
