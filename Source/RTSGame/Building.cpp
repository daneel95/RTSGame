// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::Build() {
	// TODO - Start building animation
	// TODO - Stages for building
	//FTimerHandle BuildingTimerHandler;
	//GetWorldTimerManager().SetTimer(BuildingTimerHandler, this, NULL, BuildingTime, false);

	//GetWorldTimerManager().SetTimer(DelayTimerHandler, this, &AMemoryGame_CPPGameModeBase::HandleTwoTurnedTiles, 1.0f, false);
}

void ABuilding::BuildPart(uint32 PartToBuild) {

}
