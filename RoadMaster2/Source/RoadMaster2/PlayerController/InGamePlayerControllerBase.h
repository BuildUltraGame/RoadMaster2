// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerControllerBase.generated.h"

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
	
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

protected:
	void OnHotKeyTriggered();
	void OnSelectStarted();
	void OnSelectTriggered();
	void OnSelectReleased();
};
