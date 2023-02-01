// Copyright Epic Games, Inc. All Rights Reserved.

#include "RoadMaster2GameMode.h"
#include "RoadMaster2PlayerController.h"
#include "RoadMaster2Character.h"
#include "UObject/ConstructorHelpers.h"

ARoadMaster2GameMode::ARoadMaster2GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARoadMaster2PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}