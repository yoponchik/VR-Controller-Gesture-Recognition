// Fill out your copyright notice in the Description page of Project Settings.


#include "RecordStateIndicatorWidget.h"

#include "EngineUtils.h"
#include "GestureRecognitionPlayer.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void URecordStateIndicatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Find reference to player
	for (TActorIterator<AGestureRecognitionPlayer> it(GetWorld()); it; ++it) {
		GestureRecognitionPlayer = *it;
	}

	//Bind Player's Delegate function to Widget's Change Text function 
	GestureRecognitionPlayer->OnWidgetTextChange.AddDynamic(this, &URecordStateIndicatorWidget::ChangeText);

	//Intialize Widget Text
	ChangeText(false);
}

//Changes according to GestureRecognitionPlayer->bIsRecord 
void URecordStateIndicatorWidget::ChangeText(bool bIsRecord)
{
	if(!bIsRecord){
		ImageRecordIndicator->SetVisibility(ESlateVisibility::Hidden);
		TextRecordIndicator->SetText(FText::FromString("Not Recording"));
		TextSubtext->SetText(FText::FromString("Press Right 'B' Button To START Recording. Hold Right 'Trigger' Button When Doing Gesture."));
	}
	else{
		ImageRecordIndicator->SetVisibility(ESlateVisibility::Visible);
		TextRecordIndicator->SetText(FText::FromString("Not Recording"));
		TextSubtext->SetText(FText::FromString("Press Right 'B' Button Again To STOP Recording."));
	}

}
