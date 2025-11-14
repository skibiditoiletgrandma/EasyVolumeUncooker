#include "VolumeExporterEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FVolumeExporterEditorStyle::StyleInstance = NULL;

void FVolumeExporterEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FVolumeExporterEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FVolumeExporterEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("VolumeExporterEditorStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->GetContentRootDir() / RelativePath, __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->GetContentRootDir() / RelativePath, __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->GetContentRootDir() / RelativePath, __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->GetContentRootDir() / RelativePath, __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->GetContentRootDir() / RelativePath, __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FVolumeExporterEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("VolumeExporterEditorStyle"));
	Style->SetContentRootDir(IPluginManager::Get().FindPlugin("VolumeExporter")->GetBaseDir() / TEXT("Resources"));

	Style->Set("VolumeExporterEditorStyle.MenuIcon", new IMAGE_BRUSH(TEXT("Icon16.png"), Icon16x16));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FVolumeExporterEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FVolumeExporterEditorStyle::Get()
{
	return *StyleInstance;
}