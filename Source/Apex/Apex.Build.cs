using UnrealBuildTool;

public class Apex : ModuleRules
{
	public Apex(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"ChaosVehicles",   // UChaosWheeledVehicleMovementComponent, AWheeledVehiclePawn, UChaosVehicleWheel
			"PhysicsCore",
			"EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
