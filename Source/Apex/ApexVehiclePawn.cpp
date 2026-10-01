#include "ApexVehiclePawn.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"

AApexVehiclePawn::AApexVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Bras + caméra, attachés au châssis (le mesh fourni par la base).
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 650.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 180.0f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 8.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = true;          // la caméra suit l'orientation de la voiture
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->FieldOfView = 90.0f;

	// Cache du composant Chaos (créé par la classe de base).
	VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
}

void AApexVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	if (!VehicleMovement)
	{
		VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	}

	// Enregistre le mapping context Enhanced Input.
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (InputContext)
			{
				Subsystem->AddMappingContext(InputContext, 0);
			}
		}
	}
}

void AApexVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC)
	{
		return;
	}

	if (ThrottleAction)
	{
		EIC->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AApexVehiclePawn::OnThrottle);
		EIC->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AApexVehiclePawn::OnThrottleReleased);
	}
	if (BrakeAction)
	{
		EIC->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AApexVehiclePawn::OnBrake);
		EIC->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AApexVehiclePawn::OnBrakeReleased);
	}
	if (SteerAction)
	{
		EIC->BindAction(SteerAction, ETriggerEvent::Triggered, this, &AApexVehiclePawn::OnSteer);
		EIC->BindAction(SteerAction, ETriggerEvent::Completed, this, &AApexVehiclePawn::OnSteerReleased);
	}
	if (HandbrakeAction)
	{
		EIC->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AApexVehiclePawn::OnHandbrakePressed);
		EIC->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AApexVehiclePawn::OnHandbrakeReleased);
	}
	if (GearUpAction)
	{
		EIC->BindAction(GearUpAction, ETriggerEvent::Started, this, &AApexVehiclePawn::OnGearUp);
	}
	if (GearDownAction)
	{
		EIC->BindAction(GearDownAction, ETriggerEvent::Started, this, &AApexVehiclePawn::OnGearDown);
	}
	if (LookAction)
	{
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AApexVehiclePawn::OnLook);
	}
	if (ResetAction)
	{
		EIC->BindAction(ResetAction, ETriggerEvent::Started, this, &AApexVehiclePawn::OnReset);
	}
}

// --- Handlers -------------------------------------------------------------

void AApexVehiclePawn::OnThrottle(const FInputActionValue& Value)
{
	if (VehicleMovement) { VehicleMovement->SetThrottleInput(Value.Get<float>()); }
}

void AApexVehiclePawn::OnThrottleReleased(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement) { VehicleMovement->SetThrottleInput(0.0f); }
}

void AApexVehiclePawn::OnBrake(const FInputActionValue& Value)
{
	if (VehicleMovement) { VehicleMovement->SetBrakeInput(Value.Get<float>()); }
}

void AApexVehiclePawn::OnBrakeReleased(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement) { VehicleMovement->SetBrakeInput(0.0f); }
}

void AApexVehiclePawn::OnSteer(const FInputActionValue& Value)
{
	// Axe -1..1 (gauche/droite).
	if (VehicleMovement) { VehicleMovement->SetSteeringInput(Value.Get<float>()); }
}

void AApexVehiclePawn::OnSteerReleased(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement) { VehicleMovement->SetSteeringInput(0.0f); }
}

void AApexVehiclePawn::OnHandbrakePressed(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement) { VehicleMovement->SetHandbrakeInput(true); }
}

void AApexVehiclePawn::OnHandbrakeReleased(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement) { VehicleMovement->SetHandbrakeInput(false); }
}

void AApexVehiclePawn::OnGearUp(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement)
	{
		VehicleMovement->SetTargetGear(VehicleMovement->GetCurrentGear() + 1, true);
	}
}

void AApexVehiclePawn::OnGearDown(const FInputActionValue& /*Value*/)
{
	if (VehicleMovement)
	{
		VehicleMovement->SetTargetGear(VehicleMovement->GetCurrentGear() - 1, true);
	}
}

void AApexVehiclePawn::OnLook(const FInputActionValue& Value)
{
	// Regard libre autour de la voiture (optionnel). Vector2D : X = yaw, Y = pitch.
	const FVector2D Axis = Value.Get<FVector2D>();
	if (SpringArm)
	{
		SpringArm->AddLocalRotation(FRotator(0.0f, Axis.X, 0.0f));
	}
}

void AApexVehiclePawn::OnReset(const FInputActionValue& /*Value*/)
{
	// Remet la voiture à plat sur place (sortie de tonneau).
	FRotator Rot = GetActorRotation();
	Rot.Pitch = 0.0f;
	Rot.Roll = 0.0f;
	SetActorRotation(Rot);
	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 100.0f));

	if (UPrimitiveComponent* Body = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Body->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Body->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}
}
