// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LandFormPawn.generated.h"

class ATrafficSignActor;
class ATrack;
class AMovableUnits;
class USphereComponent;

USTRUCT(BlueprintType)
struct FConnectedTrack
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta = (Tooltip = "道路"))
	ATrack* Track;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta = (Tooltip = "路标"))
	ATrafficSignActor* Sign;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta = (Tooltip = "是否阻塞"))
	bool IsJam = false;
};


UCLASS()
class ROADMASTER2_API ALandFormPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALandFormPawn();

	UPROPERTY(BlueprintReadWrite,Replicated)
	USphereComponent* Collider;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Replicated)
	TArray<FConnectedTrack> ConnectedTrackList;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta = (Tooltip = "玩家所属的Index"),Replicated)
	int32 PlayerIndex;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//执行碰撞的覆写接口
	UFUNCTION(BlueprintCallable)
	virtual void ExecUnitCollision(AMovableUnits* Unit);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

};
