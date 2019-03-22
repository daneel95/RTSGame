// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSAICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ARTSAICharacterController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

};
