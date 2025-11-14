#include "VolumeExporterEditorSettings.h"

UVolumeExporterEditorSettings::UVolumeExporterEditorSettings()
{
	bIsCheckboxChecked = false;
}

bool UVolumeExporterEditorSettings::GetIsCheckboxChecked()
{
	return GetMutableDefault<UVolumeExporterEditorSettings>()->bIsCheckboxChecked;
}

void UVolumeExporterEditorSettings::SetIsCheckboxChecked(bool bIsChecked)
{
	GetMutableDefault<UVolumeExporterEditorSettings>()->bIsCheckboxChecked = bIsChecked;
	GetMutableDefault<UVolumeExporterEditorSettings>()->SaveConfig();
}