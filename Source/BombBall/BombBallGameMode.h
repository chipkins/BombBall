// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BombBallCharacter.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "BombBallGameMode.generated.h"

/*
 * 
 */
UCLASS()
class BOMBBALL_API ABombBallGameMode : public AGameMode
{
	GENERATED_BODY()
	
	ABombBallGameMode(const FObjectInitializer& ObjectInitializer);
	
public:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Game UI")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
		TArray<ABombBallCharacter*> redTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
		int32 redScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
		TArray<ABombBallCharacter*> blueTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
		int32 blueScore;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game UI")
		APlayerController* MyController;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game UI")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
