// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


AInGamePlayerControllerBase::AInGamePlayerControllerBase()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AInGamePlayerControllerBase::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}


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


void AInGamePlayerControllerBase::OnHotKeyTriggered()
{
	UE_LOG(LogTemp,Warning,TEXT("Keyboard Pressed"))
	if(IsInputKeyDown(EKeys::A))
	{
		
	}
}

void AInGamePlayerControllerBase::OnSelectStarted()
{
	//可能需要取消选定等操作
	UE_LOG(LogTemp,Warning,TEXT("Mouse Select"))
}

void AInGamePlayerControllerBase::OnSelectTriggered()
{
	
}

void AInGamePlayerControllerBase::OnSelectReleased()
{
}
