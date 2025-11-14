#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "VolumeExporterEditorStyle.h"

class FVolumeExporterEditorCommands : public TCommands<FVolumeExporterEditorCommands>
{
public:

	FVolumeExporterEditorCommands()
		: TCommands<FVolumeExporterEditorCommands>(TEXT("VolumeExporterEditor"), NSLOCTEXT("Contexts", "VolumeExporterEditor", "VolumeExporterEditor Plugin"), NAME_None, FVolumeExporterEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenVolumeExporterWindow;
};