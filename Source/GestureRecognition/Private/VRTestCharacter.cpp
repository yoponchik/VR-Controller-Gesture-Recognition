// Fill out your copyright notice in the Description page of Project Settings.


#include "VRTestCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Engine//LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVRTestCharacter::AVRTestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region VR Camera
	VRCamera = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	VRCamera->SetupAttachment(GetRootComponent());
#pragma endregion VR Camera

#pragma region Controllers & Hand Meshes
	//vr Hand Controllers
	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Hand"));
	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Hand"));

	LeftHand->SetupAttachment(GetRootComponent());
	RightHand->SetupAttachment(GetRootComponent());

	LeftHand->SetTrackingMotionSource(FName("Left"));
	RightHand->SetTrackingMotionSource(FName("Right"));

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));

	LeftHandMesh->SetupAttachment(LeftHand);
	RightHandMesh->SetupAttachment(RightHand);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
	if(tempMesh.Succeeded()){
		LeftHandMesh->SetSkeletalMesh(tempMesh.Object);
		LeftHandMesh->SetRelativeLocationAndRotation(FVector(-2.981260, -3.500000, 4.561753), FRotator(-25.000000, -179.999999, 89.999998));
	}

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if(tempMesh2.Succeeded()){
		RightHandMesh->SetSkeletalMesh(tempMesh2.Object);
		RightHandMesh->SetRelativeLocationAndRotation(FVector(-2.981260, 3.500000, 4.561753), FRotator(25.000000, 0.000000, 89.999999));
	}
#pragma endregion Controllers & Hand Meshes
}

// Called when the game starts or when spawned
void AVRTestCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController  = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if(PlayerController){
		auto LocalPlayer = PlayerController->GetLocalPlayer();
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
		if(Subsystem){
			Subsystem->AddMappingContext(IMC_GestureCharacterInput, 0);
		}
	}


}

// Called every frame
void AVRTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto InputSystem = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(InputSystem){
		InputSystem->BindAction(IA_VRMove, ETriggerEvent::Triggered, this, &AVRTestCharacter::Move);
	}


}

void AVRTestCharacter::Move(const FInputActionValue& Values)
{
	FVector2D Axis = Values.Get<FVector2D>();
	FVector InitialPosition = GetActorLocation();

	FVector Direction(Axis.X, Axis.Y, 0);;
	Direction.Normalize();
	
	SetActorLocation(InitialPosition + Direction * MoveSpeed * GetWorld()->DeltaTimeSeconds);

}

