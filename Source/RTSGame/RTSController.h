// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ARTSController : public APlayerController
{
	GENERATED_BODY()

private:
	/* Selecting */
	FVector SelectionFrameWorldStartPosition;
	FVector2D SelectionFrameScreenStartPosition;
	TArray<AActor*> CurrentlySelectedActors;
	FVector2D CameraMovementOffset;
	bool bCreatingSelectionFrame;
	void StartSelecting();
	void StopSelecting();

	/* Right click handler function */
	void HandleRightMouseClick();
	
protected:
	virtual void SetupInputComponent() override;

public:
	ARTSController();

	/* Create screen selection frame  */
	bool GetSelectionFrame(FIntRect& OutSelectionFrame);

	/* Create world selection frame */
	bool GetSelectionFrameWorld(FIntRect& OutSelectionFrame);

	/* Get all actors in (world) selection frame */
	void GetAllActorsInSelectionFrame(FIntRect SelectionFrame, TArray<AActor*>& SelectedActors);
	
	/* Add to camera offset - for handling screen selection frame properly */
	void AddToCameraMovementOffset(FVector2D OffsetToAdd);

	void PrintOnScreen(FString Text);

};
