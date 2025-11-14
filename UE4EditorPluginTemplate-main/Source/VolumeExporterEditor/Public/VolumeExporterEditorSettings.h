#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VolumeExporterEditorSettings.generated.h"

UCLASS(config = Editor, defaultconfig)
class VOLUMEEXPORTEREDITOR_API UVolumeExporterEditorSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UVolumeExporterEditorSettings();

	static bool GetIsCheckboxChecked();
	static void SetIsCheckboxChecked(bool bIsChecked);

private:
	UPROPERTY(config)
	bool bIsCheckboxChecked;
};