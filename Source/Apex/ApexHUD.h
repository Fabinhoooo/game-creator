#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ApexHUD.generated.h"

/**
 * HUD télémétrie minimal : vitesse (km/h), régime (RPM), rapport engagé.
 * Dessin Canvas simple (remplaçable par de l'UMG plus tard).
 */
UCLASS()
class APEX_API AApexHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
};
