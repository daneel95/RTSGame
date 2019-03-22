// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSGameGameModeBase.h"
#include "RTSController.h"
#include "RTSCameraPawn.h"
#include "RTSHud.h"


ARTSGameGameModeBase::ARTSGameGameModeBase() {
	PlayerControllerClass = ARTSController::StaticClass();
	DefaultPawnClass = ARTSCameraPawn::StaticClass();
	HUDClass = ARTSHud::StaticClass();
}
