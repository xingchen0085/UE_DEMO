// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Test8GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEST8_API ATest8GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
		virtual void StartPlay() override;
	
	
};
