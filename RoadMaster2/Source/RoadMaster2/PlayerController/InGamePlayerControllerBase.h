// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
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
#pragma region UIs
	
	//主UI
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UUserWidget> BattleMainUI;
	
	//暂停UI
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UUserWidget> SuspendUI;
	
	//结束UI
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UUserWidget> BattleEndUI;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OpenBattleHUD();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OpenSuspendHUD();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OpenEndHUD();
	
	//设置当前的唯一主UI.同时只会有一个UI存在
	UFUNCTION(BlueprintCallable)
	void SetCurrentShowingUI(UUserWidget* UIWidget);
	
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* CurrentUI;

#pragma  endregion UIs

	
	//标记匹配进来的玩家序号
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerIndex;

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
