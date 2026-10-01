#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "ApexVehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UChaosWheeledVehicleMovementComponent;
struct FInputActionValue;

/**
 * Pawn voiture joueur. Dérive de AWheeledVehiclePawn (plugin ChaosVehicles), qui
 * fournit déjà un SkeletalMeshComponent + un UChaosWheeledVehicleMovementComponent.
 * Ici on ajoute : caméra poursuite, Enhanced Input, passage de rapports manuel.
 *
 * La config physique (moteur/boîte/diff/roues) se règle dans le Blueprint dérivé
 * (Details panel) — voir SETUP-UNREAL.md pour les valeurs hardcore recommandées.
 */
UCLASS()
class APEX_API AApexVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	AApexVehiclePawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// --- Caméra ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Apex|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Apex|Camera")
	TObjectPtr<UCameraComponent> Camera;

	// --- Enhanced Input (assigner les assets dans le Blueprint dérivé) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> ThrottleAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> BrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> SteerAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> HandbrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> GearUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> GearDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apex|Input")
	TObjectPtr<UInputAction> ResetAction;

private:
	// Cache du composant de mouvement Chaos (roues).
	TObjectPtr<UChaosWheeledVehicleMovementComponent> VehicleMovement;

	// Handlers d'input.
	void OnThrottle(const FInputActionValue& Value);
	void OnThrottleReleased(const FInputActionValue& Value);
	void OnBrake(const FInputActionValue& Value);
	void OnBrakeReleased(const FInputActionValue& Value);
	void OnSteer(const FInputActionValue& Value);
	void OnSteerReleased(const FInputActionValue& Value);
	void OnHandbrakePressed(const FInputActionValue& Value);
	void OnHandbrakeReleased(const FInputActionValue& Value);
	void OnGearUp(const FInputActionValue& Value);
	void OnGearDown(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
	void OnReset(const FInputActionValue& Value);
};
