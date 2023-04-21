// Fill out your copyright notice in the Description page of Project Settings.


#include "GestureRecognitionPlayer.h"

#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Math/UnitConversion.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"

// Sets default values
AGestureRecognitionPlayer::AGestureRecognitionPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickInterval = RECORD_FREQUENCY_SECONDS;
	
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

	SphereDetectorLeft = CreateDefaultSubobject<USphereComponent>(TEXT("Left Sphere Detector"));
	SphereDetectorLeft->SetupAttachment(LeftHand);
	SphereDetectorRight = CreateDefaultSubobject<USphereComponent>(TEXT("Right Sphere Detector"));
	SphereDetectorRight->SetupAttachment(RightHand);
	
}

// Called when the game starts or when spawned
void AGestureRecognitionPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController  = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if(PlayerController){
		auto localPlayer = PlayerController->GetLocalPlayer();
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if(subsystem){
			subsystem->AddMappingContext(IMC_VRInput, 0);
		}
	}


	FString RecordingsDirectory = FPaths::ProjectDir() + "RecordingSessions/";

	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*RecordingsDirectory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*RecordingsDirectory);
	}

	
	FString FilePath = RecordingsDirectory + "MotionControllerData_" + FString::FromInt(CurrentFileIndex) + ".csv";

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		// If the file doesn't exist, add the headers to the CSV file
		FFileHelper::SaveStringToFile(CSVHeaders, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
	}
}

// Called every frame
void AGestureRecognitionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	 if (bIsRecord){
	 	Record();
	}
	
}


// Called to bind functionality to input
void AGestureRecognitionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto inputSystem = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(inputSystem){
		inputSystem->BindAction(IA_RecordMovement, ETriggerEvent::Started, this, &AGestureRecognitionPlayer::OnActionRecordMovement);
	}
}

#pragma region Record
void AGestureRecognitionPlayer::OnActionRecordMovement()
{
	UE_LOG(LogTemp, Warning,TEXT("AGestureRecognitionPlayer::RecordMovement"));

	bIsRecord = !bIsRecord;

	if (bIsRecord)
	{
		//Cache Starting Time
		RecordingStartTime = GetWorld()->GetTimeSeconds();
		FString FilePath = FPaths::ProjectDir() + "RecordingSessions/" + "MotionControllerData_" + FString::FromInt(CurrentFileIndex) + ".csv";
		FFileHelper::SaveStringToFile(CSVHeaders, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	}
	else
	{
		CurrentFileIndex++;
	}
}

void AGestureRecognitionPlayer::Record()
{
	// Reset Time
    float CurrentTime = GetWorld()->GetTimeSeconds() - RecordingStartTime;

	//Get Position of Right Hand Position and Direction
    FVector RightHandPosition = GetRelativeLocation(RightHand);
    FQuat RightHandOrientation = GetRelativeRotation(RightHand);

    FVector RightHandVelocity = GetControllerVelocity(SphereDetectorRight);
    FVector RightHandAngularVelocity = GetControllerAngularVelocity(SphereDetectorRight);

    FString PositionX = FString::SanitizeFloat(RightHandPosition.X);
    FString PositionY = FString::SanitizeFloat(RightHandPosition.Y);
    FString PositionZ = FString::SanitizeFloat(RightHandPosition.Z);

    FString RotationX = FString::SanitizeFloat(RightHandOrientation.X);
    FString RotationY = FString::SanitizeFloat(RightHandOrientation.Y);
    FString RotationZ = FString::SanitizeFloat(RightHandOrientation.Z);
    FString RotationW = FString::SanitizeFloat(RightHandOrientation.W);

    FString VelocityX = FString::SanitizeFloat(RightHandVelocity.X);
    FString VelocityY = FString::SanitizeFloat(RightHandVelocity.Y);
    FString VelocityZ = FString::SanitizeFloat(RightHandVelocity.Z);

    FString AngularVelocityX = FString::SanitizeFloat(RightHandAngularVelocity.X);
    FString AngularVelocityY = FString::SanitizeFloat(RightHandAngularVelocity.Y);
    FString AngularVelocityZ = FString::SanitizeFloat(RightHandAngularVelocity.Z);

    int32 NumDecimalPlaces = 4;
    FString CurrentTimeString = FString::SanitizeFloat(CurrentTime, NumDecimalPlaces);

    FString CSVLine = CurrentTimeString + "," + PositionX + "," + PositionY + "," + PositionZ +
        "," + VelocityX + "," + VelocityY + "," + VelocityZ +
        "," + RotationX + "," + RotationY + "," + RotationZ + "," + RotationW +
        "," + AngularVelocityX + "," + AngularVelocityY + "," + AngularVelocityZ + "\n";

    FString FilePath = FPaths::ProjectDir() + "RecordingSessions/" + "MotionControllerData_" + FString::FromInt(CurrentFileIndex) + ".csv";

    // Append the line of data to the CSV file
    FFileHelper::SaveStringToFile(CSVLine, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

	UE_LOG(LogTemp, Warning,TEXT("AGestureRecognitionPlayer::Tick - Right Hand Position: %s"), *RightHandPosition.ToString());
	UE_LOG(LogTemp, Warning,TEXT("AGestureRecognitionPlayer::Tick - Right Hand Position: X %s"), *RightHandPosition.XAxisVector.ToString());
	UE_LOG(LogTemp, Warning,TEXT("AGestureRecognitionPlayer::Tick - Right Hand Orientation: %s"), *RightHandOrientation.ToString());
	UE_LOG(LogTemp, Warning,TEXT("AGestureRecognitionPlayer::Tick - Right Hand Velocity: %s"), *RightHandVelocity.ToString());
	UE_LOG(LogTemp, Warning,TEXT("AGestureRecognitionPlayer::Tick - Right Hand Angular Velocity: %s"), *RightHandAngularVelocity.ToString());
}

#pragma endregion

#pragma region Extract Data
FVector AGestureRecognitionPlayer::GetRelativeLocation(UMotionControllerComponent* InMotionController)
{
	// Get the relative transform between the motion controller and the pawn
	FTransform MotionControllerRelativeTransform = InMotionController->GetRelativeTransform();

	// Get the location and rotation of the motion controller component
	FVector Location = InMotionController->GetComponentLocation();

	// Apply the relative transform to the location and rotation
	FVector RelativeLocation = MotionControllerRelativeTransform.TransformPosition(Location);

	return  RelativeLocation;
}

FQuat AGestureRecognitionPlayer::GetRelativeRotation(UMotionControllerComponent* InMotionController)
{
	// Get the relative transform between the motion controller and the pawn
	FTransform MotionControllerRelativeTransform = InMotionController->GetRelativeTransform();

	// Get the location and rotation of the motion controller component
	FQuat Rotation = InMotionController->GetComponentQuat();

	// Apply the relative transform to the location and rotation
	FQuat RelativeRotation = MotionControllerRelativeTransform.TransformRotation(Rotation);

	return RelativeRotation;
}

FVector AGestureRecognitionPlayer::GetControllerVelocity(USphereComponent* InSphereDetector)
{
	FVector GlobalVelocity = InSphereDetector->GetPhysicsLinearVelocity();
	AActor* ObjectWithGlobalVelocity = this;
	USceneComponent* ObjectWithLocalVelocity = Cast<USceneComponent>(InSphereDetector);

	FTransform RelativeTransform = ObjectWithGlobalVelocity->GetActorTransform().GetRelativeTransform(ObjectWithLocalVelocity->GetComponentTransform());
	FVector LocalVelocity = RelativeTransform.InverseTransformVector(GlobalVelocity);

	return LocalVelocity;
}

FVector AGestureRecognitionPlayer::GetControllerAngularVelocity(USphereComponent* InSphereDetector)
{
	FVector GlobalAngularVelocity = InSphereDetector->GetPhysicsAngularVelocityInDegrees();
	AActor* ObjectWithGlobalVelocity = this;
	USceneComponent* ObjectWithLocalVelocity = Cast<USceneComponent>(InSphereDetector);

	FTransform RelativeTransform = ObjectWithGlobalVelocity->GetActorTransform().GetRelativeTransform(ObjectWithLocalVelocity->GetComponentTransform());
	FVector LocalAngularVelocity = RelativeTransform.InverseTransformVector(GlobalAngularVelocity);

	return LocalAngularVelocity;
}


#pragma endregion


