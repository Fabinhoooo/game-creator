#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleWheel.h"
#include "ApexWheelFront.generated.h"

/**
 * Roue avant : directrice, freinée, NON motrice (RWD), pas de frein à main.
 * Valeurs de départ "sim hardcore" ; ajuste finement dans le Details panel.
 */
UCLASS()
class APEX_API UApexWheelFront : public UChaosVehicleWheel
{
	GENERATED_BODY()

public:
	UApexWheelFront();
};
