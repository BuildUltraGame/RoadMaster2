// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "RoadMaster2/Component/NavigationComponent.h"
#include "MovableUnits.generated.h"

UCLASS()
class ROADMASTER2_API AMovableUnits : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovableUnits();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UNavigationComponent* Navigator;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool CanBeLaunched = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 LinearSpeed;

	UPROPERTY(BlueprintReadWrite)
	ALandFormPawn* Spawner;

	UFUNCTION(BlueprintCallable)
	ALandFormPawn* GetStartLand();

	//if need Initialize
	UFUNCTION(BlueprintCallable)
	virtual void InitUnitByType(ALandFormPawn* StartLand);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
