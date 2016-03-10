// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBALL_API AMenu : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game UI")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	virtual void StartPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game UI")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
