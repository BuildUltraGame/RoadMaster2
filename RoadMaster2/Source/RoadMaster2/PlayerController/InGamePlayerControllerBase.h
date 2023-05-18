// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerControllerBase.generated.h"

class AMinerFactory;
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
	
	UFUNCTION()
	void OpenBattleHUD();
	
	UFUNCTION()
	void OpenSuspendHUD();
	
	UFUNCTION()
	void OpenEndHUD();

	//主UI
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UUserWidget* BattleMainUIInstance;

	//主UI
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UUserWidget* SuspendUIInstance;

	//主UI
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UUserWidget* BattleEndUIInstance;
	
	//设置当前的唯一主UI.同时只会有一个UI存在
	UFUNCTION(BlueprintCallable)
	void SetCurrentShowingUI(UUserWidget* UIWidget);
	
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* CurrentUI;

	UFUNCTION(BlueprintCallable)
	void SelectUnitCard(int32 UnitID);

	UFUNCTION(BlueprintCallable)
	void UnSelectUnitCard();

	UPROPERTY(BlueprintReadWrite)
	bool IsCardSelected;

	UPROPERTY(BlueprintReadWrite)
	int32 CurSelectCardUnitID;

#pragma  endregion UIs

	
	UPROPERTY(BlueprintReadWrite)
	AMinerFactory* CurrentFactory;

	UFUNCTION(BlueprintCallable)
	void SelectFactory(AMinerFactory* Factory);

	UFUNCTION(BlueprintCallable)
	bool SpawnUnit(FVector Destination,int32 UnitID);

	UFUNCTION(Server,Reliable)
	void SpawnUnit_Server(FVector Destination,int32 UnitID,AMinerFactory* Factory);
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerStartPoint();
	
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	AInGamePlayerControllerBase();

	//常用工具
	UFUNCTION(BlueprintCallable)
	UGameInstance* GetGameInstance();

	//标记匹配进来的玩家序号
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	int32 PlayerGamePosIndex;

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void LoginData_Server(int32 PlayerMapIndex);
	
protected:
	void OnHotKeyTriggered();
	void OnSelectStarted();
	void OnSelectTriggered();
	void OnSelectReleased();
	void LoadPCDataFromSubSys();
};
