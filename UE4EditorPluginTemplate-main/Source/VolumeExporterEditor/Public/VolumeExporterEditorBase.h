#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VolumeExporterEditorBase.generated.h"

class UVolumeExporterEditorWidget;

UCLASS(Blueprintable)
class VOLUMEEXPORTEREDITOR_API UVolumeExporterEditorBase : public UObject
{
	GENERATED_BODY()

public:
	UVolumeExporterEditorBase();

	UFUNCTION(BlueprintCallable)
	void SetEditorWidget(UVolumeExporterEditorWidget* InEditorWidget);

	UFUNCTION(BlueprintCallable)
	void CreateTheWidget();

	virtual void InitializeTheWidget();

protected:
	UPROPERTY()
	UVolumeExporterEditorWidget* EditorWidget;
};