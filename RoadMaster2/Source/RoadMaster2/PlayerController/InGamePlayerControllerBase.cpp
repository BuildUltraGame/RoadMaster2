// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerControllerBase.h"

#include "EnhancedInputComponent.h"

void AInGamePlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// 快捷键操作
		EnhancedInputComponent->BindAction(HotKeyAction, ETriggerEvent::Triggered, this, &AInGamePlayerControllerBase::OnHotKeyTriggered);

		// 选择操作
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &AInGamePlayerControllerBase::OnSelectStarted);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &AInGamePlayerControllerBase::OnSelectTriggered);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &AInGamePlayerControllerBase::OnSelectReleased);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Canceled, this, &AInGamePlayerControllerBase::OnSelectReleased);
	}
}

void AInGamePlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AInGamePlayerControllerBase::OnHotKeyTriggered()
{
	
}

void AInGamePlayerControllerBase::OnSelectStarted()
{
	//可能需要取消选定等操作
}

void AInGamePlayerControllerBase::OnSelectTriggered()
{
	
}

void AInGamePlayerControllerBase::OnSelectReleased()
{
}
