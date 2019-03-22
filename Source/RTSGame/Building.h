// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class RTSGAME_API ABuilding : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BuildingMesh;

	// Building Max Health Points
	UPROPERTY(VisibleAnywhere)
	uint32 MaxHealthPoints;
	// Building Current Health Points
	uint32 CurrentHealthPoints;
	// Building Build time required (in seconds)
	UPROPERTY(VisibleAnywhere)
	uint32 BuildingTime;

public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE uint32 GetMaxHealthPoints() { return MaxHealthPoints; }
	FORCEINLINE uint32 GetCurrentHealthPoints() { return CurrentHealthPoints; }
	FORCEINLINE uint32 GetBuildingTime() { return BuildingTime; }
	// Build the whole building
	void Build();
	// Build a part of the building (change static mesh component according to the part we are at)
	void BuildPart(uint32 PartToBuild);
};
