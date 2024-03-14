// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GestureRecognitionPlayer.generated.h"

//Delegate to change text in widget
	//Simpler with delegate because otherwise need Widget actor ref then Widget component ref
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWidgetTextChange, bool, bIsRecord);

const FString FILENAME = TEXT("MotionControllerData.csv");

UCLASS()
class GESTURERECOGNITION_API AGestureRecognitionPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGestureRecognitionPlayer();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Input
	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputMappingContext* IMC_VRInput;

	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputAction* IA_RecordMovement;
	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputAction* IA_FlagSegmentPressed;

#pragma endregion Input

#pragma region Camera, Controllers & Hands
	UPROPERTY(EditAnywhere, Category = "Player Settings | VR Settings")
	class UCameraComponent* VRCamera;

	UPROPERTY(EditAnywhere, Category = "Player Settings | VR Settings")
	class UMotionControllerComponent* LeftHand;
	UPROPERTY(EditAnywhere, Category = "Player Settings | VR Settings")
	class UMotionControllerComponent* RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings | VR Settings")
	class USkeletalMeshComponent* LeftHandMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings | VR Settings")
	class USkeletalMeshComponent* RightHandMesh;

	//Components used to extract controller data
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereDetectorRight;
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereDetectorLeft;
#pragma endregion Controllers & Hands

	//function called on record button press
	UFUNCTION()
	void OnActionRecordMovement();				//toggles bIsRecord flag

	//function called on flag segment button press
	//toggles FlagSegmentValue
	UFUNCTION()
	void OnActionFlagSegmentPressed();
	UFUNCTION()
	void OnActionFlagSegmentReleased();

	//Records controller movement
		//Currently, only does right motion controller
	void Record();

	int32 CurrentFileIndex = 0;
	FString CSVHeaders = "Time,Relevant Segment,RH_Relative_Position_X,RH_Relative_Position_Y,RH_Relative_Position_Z,RH_Velocity_X,RH_Velocity_Y,RH_Velocity_Z,RH_Rotation_X,RH_Rotation_YRH_Rotation_Z,RH_Rotation_W,RH_Angular_Velocity_X,RH_Angular_Velocity_Y,RH_Angular_Velocity_Z\n";

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Gesture Recognition")
	float RecordSampleRateSeconds = 0.01f;

	//Checkpoint in case user wants multiple recording sessions in single runtime
	float RecordingStartTime = 0.0f;
	
	bool bIsRecord = false;

	bool bDoingGesture = false;

	//Arbitrary, large value to help ML to detect segment
	//Can change this value in the Unreal Engine Editor
		//In GestureRecognitionStuff folder, BP_GestureRecognitionPlayer
		//Search for Gesture Recognition or FlaggedSegment Value in the search bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gesture Recognition")
	int32 FlaggedSegmentValue = 1000;

	//For getting controller data 
	FVector GetRelativeLocation(UMotionControllerComponent* InMotionController);
	FQuat GetRelativeRotation(UMotionControllerComponent* InMotionController);
	FVector GetControllerAngularVelocity(USphereComponent* InSphereDetector);
	FVector GetControllerVelocity(USphereComponent* InSphereDetector);

	//Record State Indication
	//Haptic Feedback
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gesture Recognition")
	class UHapticFeedbackEffect_Curve* HF_RecordIndicator;

	//widget text change
	FOnWidgetTextChange OnWidgetTextChange;

private:
	FVector PreviousVelocity;
	int32 CurrentSegmentValue;
	
	UPROPERTY()
	class APlayerController* PlayerController;
};
