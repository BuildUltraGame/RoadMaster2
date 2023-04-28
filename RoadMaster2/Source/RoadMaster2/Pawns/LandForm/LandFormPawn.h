// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LandFormPawn.generated.h"

class AMovableUnits;
class USphereComponent;
//
// USTRUCT()
// struct FConnectRoad
// {
// 	GENERATED_BODY()
//
// 	
// };


UCLASS()
class ROADMASTER2_API ALandFormPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALandFormPawn();

	UPROPERTY(BlueprintReadWrite)
	USphereComponent* Collider;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//执行碰撞的覆写接口
	UFUNCTION(BlueprintCallable)
	virtual void ExecUnitCollision(ALandFormPawn* CurrentLandForm);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
