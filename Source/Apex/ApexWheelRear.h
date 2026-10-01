#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleWheel.h"
#include "ApexWheelRear.generated.h"

/**
 * Roue arrière : motrice (RWD), freinée, frein à main, non directrice.
 */
UCLASS()
class APEX_API UApexWheelRear : public UChaosVehicleWheel
{
	GENERATED_BODY()

public:
	UApexWheelRear();
};
