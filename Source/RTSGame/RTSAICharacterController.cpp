// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSAICharacterController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

//void ARTSAICharacterController::MoveActorToLocation(AActor* ActorToMove, FVector MoveLocation) {
//	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
//	if (BehaviorTreeComponent) {
//		BehaviorTreeComponent->RestartTree();
//	}
//	
//	MoveToLocation(MoveLocation);
//}

void ARTSAICharacterController::BeginPlay() {
	Super::BeginPlay();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "FUTUTI PE MATA AIA PROASTA");
	MoveToLocation(FVector(-50.0f, 800.0f, -932.0f));
}