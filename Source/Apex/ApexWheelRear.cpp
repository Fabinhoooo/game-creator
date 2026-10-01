#include "ApexWheelRear.h"

UApexWheelRear::UApexWheelRear()
{
	WheelRadius = 34.0f;
	WheelWidth = 28.0f;

	AxleType = EAxleType::Rear;
	bAffectedBySteering = false;
	bAffectedByEngine = true;     // RWD : l'arrière entraîne
	bAffectedByBrake = true;
	bAffectedByHandbrake = true;

	MaxSteerAngle = 0.0f;

	MaxBrakeTorque = 3000.0f;     // moins qu'à l'avant
	MaxHandBrakeTorque = 6000.0f;

	SuspensionMaxRaise = 8.0f;
	SuspensionMaxDrop = 12.0f;
	SuspensionDampingRatio = 0.5f;
	SpringRate = 270.0f;
	SpringPreload = 50.0f;

	FrictionForceMultiplier = 3.0f;
}
