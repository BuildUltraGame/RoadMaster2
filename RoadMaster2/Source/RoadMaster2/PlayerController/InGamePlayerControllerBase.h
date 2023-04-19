// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerControllerBase.generated.h"

class AStartPoint;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class ROADMASTER2_API AInGamePlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* HotKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SelectAction;
	
	//标记匹配进来的玩家序号
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerIndex;
	
	UFUNCTION(BlueprintCallable)
	AStartPoint* GetPlayerStartPoint();

	UFUNCTION(BlueprintCallable)
	void SetPlayerStartPoint();
	
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	AInGamePlayerControllerBase();

	//常用工具
	UFUNCTION(BlueprintCallable)
	UGameInstance* GetGameInstance();

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	int32 LocalPlayerIndex;

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void LoginData_Server(int32 PlayerMapIndex);
	
protected:
	void OnHotKeyTriggered();
	void OnSelectStarted();
	void OnSelectTriggered();
	void OnSelectReleased();
	void LoadPCDataFromSubSys();
};
