#include "ApexWheelFront.h"

UApexWheelFront::UApexWheelFront()
{
	// Dimensions (cm). Rayon ~34 cm = pneu sport typique.
	WheelRadius = 34.0f;
	WheelWidth = 25.0f;

	// Rôle de la roue.
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	bAffectedByEngine = false;   // RWD : l'avant n'est pas moteur
	bAffectedByBrake = true;
	bAffectedByHandbrake = false;

	// Direction.
	MaxSteerAngle = 40.0f;

	// Freinage (N·m). Plus de frein à l'avant (répartition ~60/40).
	MaxBrakeTorque = 4500.0f;
	MaxHandBrakeTorque = 0.0f;

	// Suspension (cm de course / raideur). Hardcore = ferme.
	SuspensionMaxRaise = 8.0f;
	SuspensionMaxDrop = 12.0f;
	SuspensionDampingRatio = 0.5f;
	SpringRate = 250.0f;
	SpringPreload = 50.0f;

	// Adhérence : >1 = plus de grip. Monte pour des slicks.
	FrictionForceMultiplier = 3.0f;
}
