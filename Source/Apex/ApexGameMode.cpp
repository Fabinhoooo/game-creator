#include "ApexGameMode.h"
#include "ApexHUD.h"

AApexGameMode::AApexGameMode()
{
	HUDClass = AApexHUD::StaticClass();
	// DefaultPawnClass : laisse à None ici et place/possède le pawn voiture dans le
	// niveau, OU assigne ton Blueprint BP_ApexVehicle via un GameMode Blueprint dérivé.
	DefaultPawnClass = nullptr;
}
