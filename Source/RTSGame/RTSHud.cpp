// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSHud.h"
#include "RTSController.h"
#include "UnitActor.h"


void ARTSHud::DrawSelectionFrame() {
	ARTSController* PlayerController = Cast<ARTSController>(PlayerOwner);
	if (!PlayerController) {
		return;
	}

	FIntRect SelectionFrame; // We can get at any point the selection frame from player controller
	// If not in selection mode
	if (!PlayerController->GetSelectionFrame(SelectionFrame)) {
		return;
	}

	// Draw the actual selection frame
	DrawRect(
		FLinearColor(0, 1, 0, .15f),
		SelectionFrame.Min.X,
		SelectionFrame.Min.Y,
		SelectionFrame.Width(),
		SelectionFrame.Height()
		);
	
	SelectActors(SelectedActors, SelectionFrame);
}

// Not doing good stuff
void ARTSHud::SelectActors(TArray<AActor*>& ActorsInRectangle, FIntRect SelectionFrame) {
	GetActorsInSelectionRectangle<AActor>(
		SelectionFrame.Min, 
		SelectionFrame.Max, 
		ActorsInRectangle, 
		false, 
		false
	);
}

void ARTSHud::DrawHUD() {
	Super::DrawHUD();

	DrawSelectionFrame();
}
