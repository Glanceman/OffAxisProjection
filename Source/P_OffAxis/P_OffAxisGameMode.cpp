// Copyright Epic Games, Inc. All Rights Reserved.

#include "P_OffAxisGameMode.h"
#include "P_OffAxisCharacter.h"
#include "UObject/ConstructorHelpers.h"

AP_OffAxisGameMode::AP_OffAxisGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
