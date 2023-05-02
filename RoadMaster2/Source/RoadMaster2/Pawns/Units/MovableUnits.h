// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "MovableUnits.generated.h"

class ATrack;
UCLASS()
class ROADMASTER2_API AMovableUnits : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovableUnits();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta = (Tooltip = "该单位是否一定要沿路行驶"),Replicated)
	bool MustMoveOnLine = true;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta = (Tooltip = "该单位是否在终点停止"),Replicated)
	bool IsStopAtDestination = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta = (Tooltip = "单位线速度"),Replicated)
	int32 LinearSpeed;

	UPROPERTY(BlueprintReadWrite,Replicated)
	ALandFormPawn* Spawner;

	//前往目标点使用的路线，用以选路
	UPROPERTY(BlueprintReadWrite,Replicated)
	ATrack* ComingTrack;

	//当前所在线路，用于操作移动
	UPROPERTY(BlueprintReadWrite,Replicated)
	ATrack* CurrentTrack;

	//if need Initialize
	UFUNCTION(BlueprintCallable)
	virtual void InitUnitByType(ALandFormPawn* StartLand,FVector InDestination);

	UPROPERTY(Replicated)
	FVector Destination;

	UPROPERTY(Replicated)
	int32 PlayerIndex;

	UPROPERTY(BlueprintReadWrite)
	USphereComponent* Collider;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;

};
