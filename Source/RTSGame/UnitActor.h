// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitActor.generated.h"

UCLASS()
class RTSGAME_API AUnitActor : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* UnitMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SelectionMesh;

	// TODO - Unit Type Enum 
	/* Unit movement speed */
	UPROPERTY(VisibleAnywhere)
	float MovementSpeed;

	/* Unit Damage */
	UPROPERTY(VisibleAnywhere)
	float Damage;

	/* Attack Speed */
	UPROPERTY(VisibleAnywhere)
	float AttackSpeed;

	/* Unit Health */
	UPROPERTY(VisibleAnywhere)
	float Health;

public:	
	// Sets default values for this actor's properties
	AUnitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Getters */
	FORCEINLINE float GetMovementSpeed() { return MovementSpeed; }
	FORCEINLINE float GetDamage() { return Damage; }
	FORCEINLINE float GetAttackSpeed() { return AttackSpeed; }
	FORCEINLINE float GetHealth() { return Health; }

	void MoveUnitToLocation(FVector MoveLocation);
	void SetSelectionIndicatorVisibility(bool isVisible);
};
