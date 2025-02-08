// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/RotationMatrix.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;


	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input mapping context to the Enhanced Input Subsystem
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}	
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);

}

// Handles movement input
void ASCharacter::Move(const FInputActionValue& Value)
//{
//	// Get movement input as a 2D vector
//	const FVector2D MovementVector = Value.Get<FVector2D>();
//
//	// Get the controller rotation & flatten it 
//	// Ignore pitch & roll
//	FRotator ControlRot = Controller->GetControlRotation();
//	ControlRot.Pitch = 0.0f;
//	ControlRot.Roll= 0.0f;
//
//	// Calculate forward and right movement directions
//	const FVector Forward = FRotationMatrix(ControlRot).GetScaledAxes(EAxis::X);
//	const FVector Right = FRotationMatrix(ControlRot).GetScaledAxes(EAxis::Y);
//
//	// Apply movement input in the forward & right directions
//	AddMovementInput(Forward, MovementVector.X);
//	AddMovementInput(Right, MovementVector.Y);
//}
//void ASCharacter::Move(const FInputActionValue& Value)
{
	// Get movement input as a 2D vector
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Get the controller's rotation and flatten it (ignore pitch and roll)
	FRotator ControlRot = Controller->GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Calculate forward and right movement directions
	const FVector Forward = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::X);
	const FVector Right = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	// Apply movement input in the forward and right directions
	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);
}


// Handles look input with a mouse or gamepad
void ASCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	// Add yaw and pitch input based on look axis values
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerYawInput(LookAxisValue.X);

	}
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement & look input actions
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
	}
}