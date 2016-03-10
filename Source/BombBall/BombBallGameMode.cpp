// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBall.h"
#include "BombBallGameMode.h"

ABombBallGameMode::ABombBallGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/BombBallBlueprints/BP_BombBallCharacter.BP_BombBallCharacter_C'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

void ABombBallGameMode::StartPlay()
{
	Super::StartPlay();

	ChangeMenuWidget(StartingWidgetClass);

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World"));
	}
}

void ABombBallGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}