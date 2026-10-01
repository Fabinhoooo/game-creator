#include "ApexHUD.h"

#include "ApexVehiclePawn.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void AApexHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas) { return; }

	const APlayerController* PC = GetOwningPlayerController();
	if (!PC) { return; }

	const AApexVehiclePawn* Car = Cast<AApexVehiclePawn>(PC->GetPawn());
	if (!Car) { return; }

	const UChaosWheeledVehicleMovementComponent* Mv =
		Cast<UChaosWheeledVehicleMovementComponent>(Car->GetVehicleMovementComponent());
	if (!Mv) { return; }

	// GetForwardSpeed() est en cm/s -> km/h.
	const float SpeedKmh = FMath::Abs(Mv->GetForwardSpeed()) * 0.036f;
	const float Rpm = Mv->GetEngineRotationSpeed();
	const int32 Gear = Mv->GetCurrentGear();

	FString GearStr;
	if (Gear > 0)       { GearStr = FString::FromInt(Gear); }
	else if (Gear == 0) { GearStr = TEXT("N"); }
	else                { GearStr = TEXT("R"); }

	UFont* Font = GEngine ? GEngine->GetLargeFont() : nullptr;
	if (!Font) { return; }

	const float X = Canvas->ClipX - 260.0f;
	float Y = Canvas->ClipY - 140.0f;

	const FLinearColor White(1.0f, 1.0f, 1.0f, 1.0f);
	const FLinearColor Accent(1.0f, 0.55f, 0.1f, 1.0f);

	Canvas->SetDrawColor(White.ToFColor(true));
	Canvas->DrawText(Font, FString::Printf(TEXT("%3.0f km/h"), SpeedKmh), X, Y);
	Y += 36.0f;
	Canvas->DrawText(Font, FString::Printf(TEXT("%5.0f rpm"), Rpm), X, Y);
	Y += 36.0f;
	Canvas->SetDrawColor(Accent.ToFColor(true));
	Canvas->DrawText(Font, FString::Printf(TEXT("Rapport: %s"), *GearStr), X, Y);
}
