// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerControllerBase.h"

#include <string>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "RoadMaster2/GameMode/InGameGameModeBase.h"
#include "RoadMaster2/SubSystem/RMGameInstanceSubsystem.h"



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
	//从大厅切换进来的时候，应该去读取相关的数据
	LoadPCDataFromSubSys();
}


void AInGamePlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// 快捷键操作
		EnhancedInputComponent->BindAction(HotKeyAction, ETriggerEvent::Started, this, &AInGamePlayerControllerBase::OnHotKeyTriggered);
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
		UGameInstance* GameInstance = GetGameInstance();
		auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
		UE_LOG(LogTemp, Warning, TEXT("ThisClientIndex = %d"), RMSys->CurrentInMapIndex);
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

void AInGamePlayerControllerBase::SetPlayerStartPoint()
{
	UWorld* World = GetWorld();
	FName Tag = FName(*FString::Printf(TEXT("Player%d"),LocalPlayerIndex));
	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsWithTag(World,Tag,ActorArray);
	for(auto actor: ActorArray)
	{
		auto StartPoint = static_cast<APlayerStart*>(actor);
		if (IsValid(StartPoint))
		{
			const auto Camera = GetPawn();
			Camera->SetActorLocation(StartPoint->GetActorLocation());
		}
	}
}

UGameInstance* AInGamePlayerControllerBase::GetGameInstance()
{
	UWorld* World = GetWorld();
	UGameInstance* GameInstance = World->GetGameInstance();
	return  GameInstance;
}

void AInGamePlayerControllerBase::LoadPCDataFromSubSys()
{
	if (GIsClient)
	{
		UGameInstance* GameInstance =GetGameInstance();
		auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
		if (RMSys)
		{
			LocalPlayerIndex = RMSys->CurrentInMapIndex;
		}
		LoginData_Server(LocalPlayerIndex);
	}	
}

void AInGamePlayerControllerBase::LoginData_Server_Implementation(int32 PlayerMapIndex)
{
	if (GIsServer)
	{
		LocalPlayerIndex = PlayerIndex;
		UWorld* World = GetWorld();
		auto GameMode = static_cast<AInGameGameModeBase*>(World->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CheckWaitingForConnectOver();
		}
	}
}

void AInGamePlayerControllerBase::SetCurrentShowingUI(UUserWidget* UIWidget)
{
	if (CurrentUI)
	{
		CurrentUI->RemoveFromParent();
	}
	CurrentUI = UIWidget;
}

