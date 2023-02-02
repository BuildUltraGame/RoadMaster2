// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RoadMaster2/Component/UnitLauncherComponent.h"
#include "LandFormPawn.generated.h"

UCLASS()
class ROADMASTER2_API ALandFormPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALandFormPawn();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UUnitLauncherComponent* UnitLauncher;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<ALandFormPawn*,bool> NeighborMap;

	UFUNCTION(BlueprintCallable)
	FVector GetWayPoint();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USphereComponent* WayPoint;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
