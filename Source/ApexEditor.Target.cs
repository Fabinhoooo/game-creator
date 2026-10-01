using UnrealBuildTool;
using System.Collections.Generic;

public class ApexEditorTarget : TargetRules
{
	public ApexEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("Apex");
	}
}
