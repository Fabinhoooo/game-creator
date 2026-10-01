#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ApexGameMode.generated.h"

/**
 * GameMode : branche le HUD télémétrie. Le pawn par défaut se place dans le niveau
 * (ou s'assigne dans le Blueprint de GameMode dérivé).
 */
UCLASS()
class APEX_API AApexGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AApexGameMode();
};
