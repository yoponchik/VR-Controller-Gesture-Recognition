// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "VRTestCharacter.generated.h"

UCLASS()
class GESTURERECOGNITION_API AVRTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRTestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputMappingContext* IMC_GestureCharacterInput;
		
	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	class UInputAction* IA_VRMove;

	UPROPERTY(EditAnywhere, Category = "Player Settings | Inputs | Movement")
	float MoveSpeed = 500;

	UFUNCTION()
	void Move(const FInputActionValue& Values);

protected:
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
#pragma endregion Controllers & Hands
};
