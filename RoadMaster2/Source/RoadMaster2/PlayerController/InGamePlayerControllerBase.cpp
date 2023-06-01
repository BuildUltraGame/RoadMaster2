// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "RoadMaster2/Data/UnitInfoBase.h"
#include "RoadMaster2/GameMode/InGameGameModeBase.h"
#include "RoadMaster2/GameState/InBattleGameState.h"
#include "RoadMaster2/Pawns/LandForm/MinerFactory.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"
#include "RoadMaster2/PlayerState/InGamePlayerStateBase.h"
#include "RoadMaster2/SubSystem/RMGameInstanceSubsystem.h"
#include "RoadMaster2/UI/RMCommandUserWidget.h"


AInGamePlayerControllerBase::AInGamePlayerControllerBase()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CurrentFactory = nullptr;
	CurSelectCardUnitID = 0;
	IsCardSelected = false;
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

#pragma region Control functions

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

#pragma endregion Control functions

#pragma region Initial functions

void AInGamePlayerControllerBase::SetPlayerStartPoint()
{
	UWorld* World = GWorld;
	FName Tag = FName(*FString::Printf(TEXT("Player%d"),PlayerGamePosIndex));
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


void AInGamePlayerControllerBase::LoadPCDataFromSubSys()
{
	if (GIsClient)
	{
		UGameInstance* GameInstance =GetGameInstance();
		auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
		if (RMSys)
		{
			PlayerGamePosIndex = RMSys->CurrentInMapIndex;
		}
		LoginData_Server(PlayerGamePosIndex);
	}	
}

void AInGamePlayerControllerBase::LoginData_Server_Implementation(int32 PlayerMapIndex)
{
	if (GIsServer)
	{
		PlayerGamePosIndex = PlayerMapIndex;
		UWorld* World = GWorld;
		auto GameMode = static_cast<AInGameGameModeBase*>(World->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CheckWaitingForConnectOver();
		}
	}
}

void AInGamePlayerControllerBase::ReportSubStateSetSuccess_Implementation()
{	
	AInBattleGameState* GameState = GWorld->GetGameState<AInBattleGameState>();
	if (IsValid(GameState))
	{
		GameState->SubStateSetSuccess();
	}
}

#pragma endregion Initial functions

UGameInstance* AInGamePlayerControllerBase::GetGameInstance()
{
	UWorld* World = GWorld;
	UGameInstance* GameInstance = World->GetGameInstance();
	return  GameInstance;
}



bool AInGamePlayerControllerBase::SpawnUnit(FVector Destination, int32 UnitID)
{
	//未选定
	if (CurrentFactory == nullptr)
	{
		return false;
	}
	UWorld* World = GWorld;
	AInBattleGameState* GameState = World->GetGameState<AInBattleGameState>();
	//todo 由于CD 机制是老机制，这里相信UI层的CD,以后可以加校验
	auto UnitInfo = GameState->GetUnitInfoByID(UnitID);
	auto InGamePlayerState = static_cast<AInGamePlayerStateBase*>(PlayerState);
	//资源不足
	if (InGamePlayerState->Fund < UnitInfo->Cost)
	{
		return false;
	}
	if (UnitInfo)
	{
		SpawnUnit_Server(Destination,UnitID,CurrentFactory);
		return true;
	}
	return false; 
}

void AInGamePlayerControllerBase::SpawnUnit_Server_Implementation(FVector Destination, int32 UnitID,
	AMinerFactory* Factory)
{
	UWorld* World = GWorld;
	AInBattleGameState* GameState = World->GetGameState<AInBattleGameState>();
	auto UnitInfo = GameState->GetUnitInfoByID(UnitID);
	auto Location = Factory->GetActorLocation();
	auto Rotation = Factory->GetActorRotation();
	auto Unit = World->SpawnActor<AMovableUnits>(UnitInfo->UnitClass,Location,Rotation);
	Unit->Spawner = Factory;
	Unit->Destination = Destination;
	Unit->UnitID = UnitID;
	Unit->PlayerIndex = PlayerGamePosIndex;
}

#pragma region UI

//切换当前UI
void AInGamePlayerControllerBase::SetCurrentShowingUI(URMCommandUserWidget* UIWidget)
{
	if (CurrentUI)
	{
		CurrentUI->SetVisibility(ESlateVisibility::Collapsed);
	}
	CurrentUI = UIWidget;
	CurrentUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void AInGamePlayerControllerBase::OpenBattleHUD()
{
	if (!IsValid(BattleMainUIInstance)&&IsValid(BattleMainUI))
	{
		BattleMainUIInstance = CreateWidget<URMCommandUserWidget>(this,BattleMainUI);
		BattleMainUIInstance ->AddToViewport();
	}
	SetCurrentShowingUI(BattleMainUIInstance);
}

void AInGamePlayerControllerBase::OpenSuspendHUD()
{
	if (!IsValid(SuspendUIInstance)&&IsValid(SuspendUI))
	{
		SuspendUIInstance = CreateWidget<URMCommandUserWidget>(this,SuspendUI);
		SuspendUIInstance->AddToViewport();
	}
	SetCurrentShowingUI(SuspendUIInstance);
}

void AInGamePlayerControllerBase::OpenEndHUD()
{
	if (!IsValid(BattleEndUIInstance)&&IsValid(BattleEndUI))
	{
		BattleEndUIInstance = CreateWidget<URMCommandUserWidget>(this,BattleEndUI);
		BattleEndUIInstance->AddToViewport();
	}
	SetCurrentShowingUI(BattleEndUIInstance);
}


void AInGamePlayerControllerBase::SelectFactory(AMinerFactory* Factory)
{
	UWorld* World = GWorld;
	AInBattleGameState* GameState = World->GetGameState<AInBattleGameState>();
	if (GameState->InGameSubState == EInGameSubState::GamePlay)
	{
		CurrentFactory = Factory;
		OpenBattleHUD();
		if (CurrentUI != BattleMainUIInstance)
		{
			CurrentUI->RemoveFromParent();
			CurrentUI = BattleMainUIInstance;
		}
		if (IsValid(BattleMainUIInstance))
		{
			if (IsValid(CurrentFactory))
			{
				BattleMainUIInstance->ExecBluePrintCommand("ShowPanel");
			}
			else
			{
				BattleMainUIInstance->ExecBluePrintCommand("HidePanel");
			}
		}		
	}	
}

void AInGamePlayerControllerBase::UnSelectFactory()
{
	UWorld* World = GWorld;//注意：GetWorld()不一定有值，全局变量GWorld更稳一些
	AInBattleGameState* GameState = World->GetGameState<AInBattleGameState>();
	if (GameState->InGameSubState == EInGameSubState::GamePlay)
	{
		CurrentFactory = nullptr;
		if (IsValid(BattleMainUIInstance))
		{
			BattleMainUIInstance->ExecBluePrintCommand("HidePanel");
		}		
	}	
}

void AInGamePlayerControllerBase::SelectUnitCard(int32 UnitID)
{
	CurSelectCardUnitID = UnitID;
	IsCardSelected = true;
	if (IsValid(BattleMainUIInstance))
	{
		BattleMainUIInstance->ExecBluePrintCommand("CardSelect");
	}
	// todo:可能需要判断拖拽效果
}

void AInGamePlayerControllerBase::UnSelectUnitCard()
{
	CurSelectCardUnitID = 0;
	IsCardSelected = false;
	if (IsValid(BattleMainUIInstance))
	{
		BattleMainUIInstance->ExecBluePrintCommand("EndSelect");
	}
	// todo:可能需要判断拖拽效果
}

#pragma endregion 
