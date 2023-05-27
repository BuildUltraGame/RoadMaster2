// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMCommandUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API URMCommandUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)//注意！ BlueprintNativeEvent、BlueprintImplementableEvent 传入FString需要const/&修饰 FName则不需要
	int32 ExecBluePrintCommand(const FString& Command);
	
};
