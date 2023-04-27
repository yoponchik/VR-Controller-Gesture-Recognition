// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GestureRecognitionPlayer.generated.h"

const float RECORD_FREQUENCY_SECONDS = 0.1f;
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

	UPROPERTY()
	class APlayerController* PlayerController;
	
#pragma region Input
	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputMappingContext* IMC_VRInput;

	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputAction* IA_RecordMovement;

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


	UFUNCTION()
	void OnActionRecordMovement();

	void Record();


	int32 CurrentFileIndex = 0;
	FString CSVHeaders = "Time,Right Hand Position X,Right Hand Position Y,Right Hand Position Z,Right Hand Velocity X,Right Hand Velocity Y,Right Hand Velocity Z,Right Hand Orientation X,Right Hand Orientation Y,Right Hand Orientation Z,Right Hand Angular Velocity X,Right Hand Angular Velocity Y,Right Hand Angular Velocity Z,Right Hand Angular Velocity W, \n";

	
	float RecordingStartTime = 0.0f;
	bool bIsRecord = false;


	//For getting controller data 
	FVector GetRelativeLocation(UMotionControllerComponent* InMotionController);
	FQuat GetRelativeRotation(UMotionControllerComponent* InMotionController);
	FVector GetControllerAngularVelocity(USphereComponent* InSphereDetector);
	FVector GetControllerVelocity(USphereComponent* InSphereDetector);

	FVector PreviousVelocity;


};
