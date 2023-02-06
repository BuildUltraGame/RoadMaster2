// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandFormPawn.h"
#include "StartPoint.generated.h"

class UUnitSpawnerComponent;
/**
 * 
 */
UCLASS()
class ROADMASTER2_API AStartPoint : public ALandFormPawn
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UUnitSpawnerComponent* UnitSpawner;

/** Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TestSpawnAction;

	UFUNCTION(BlueprintCallable)
	void SpawnUnit(const FInputActionValue& Value);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
