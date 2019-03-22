// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHud.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ARTSHud : public AHUD
{
	GENERATED_BODY()

private:
	// Selected actors at a given time
	TArray<AActor*> SelectedActors;
	
public:
	virtual void DrawHUD() override;
	void DrawSelectionFrame();
	FORCEINLINE TArray<AActor*> GetSelectedActors() { return SelectedActors; }

private:
	void SelectActors(TArray<AActor*>& ActorsInRectangle, FIntRect SelectionFrame);
};
