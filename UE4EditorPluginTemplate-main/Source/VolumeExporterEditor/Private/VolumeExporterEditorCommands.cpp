#include "VolumeExporterEditorCommands.h"

#define LOCTEXT_NAMESPACE "FVolumeExporterEditorModule"

void FVolumeExporterEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenVolumeExporterWindow, "Volume Exporter", "Opens Volume Exporter Window", EUserInterfaceActionType::Check, FInputChord());
}

#undef LOCTEXT_NAMESPACE