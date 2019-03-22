// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitActor.h"
#include "RTSAICharacterController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceConstant.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "RTSController.h"

// Sets default values
AUnitActor::AUnitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	SelectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionMesh"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> SelectionMaterialInstance(TEXT("MaterialInstanceConstant'/Game/Materials/SelectionCircle_Inst.SelectionCircle_Inst'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneStaticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	SelectionMesh->SetWorldScale3D(FVector(1.5f, 1.5f, 1.0f));
	SelectionMesh->SetStaticMesh(PlaneStaticMesh.Object);
	SelectionMesh->SetMaterial(0, SelectionMaterialInstance.Object);
	SetSelectionIndicatorVisibility(false);

	UnitMesh->AttachTo(RootComponent);
	SelectionMesh->AttachTo(RootComponent);

	this->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	// TODO - Switch Case on Unit Type. For now just some random values
	MovementSpeed = 1000.0f;
	Health = 100.0f;
	Damage = 10.0f;
	AttackSpeed = 1.0f;
}

// Called when the game starts or when spawned
void AUnitActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitActor::MoveUnitToLocation(FVector MoveLocation) {
	MoveLocation.Z = GetActorLocation().Z;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, MoveLocation.ToString());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), MoveLocation);
}

void AUnitActor::SetSelectionIndicatorVisibility(bool isVisible) {
	SelectionMesh->SetVisibility(isVisible);
}
