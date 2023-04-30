// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecordStateIndicatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class GESTURERECOGNITION_API URecordStateIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* TextRecordIndicator;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* TextSubtext;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UImage* ImageRecordIndicator;

	virtual void NativeConstruct() override;

	UPROPERTY()
	class AGestureRecognitionPlayer* GestureRecognitionPlayer;
	
	UFUNCTION()
	void ChangeText(bool bIsRecord);
};
