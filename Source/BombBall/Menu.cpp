// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBall.h"
#include "Menu.h"


void AMenu::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	ChangeMenuWidget(StartingWidgetClass);
}

void AMenu::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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

