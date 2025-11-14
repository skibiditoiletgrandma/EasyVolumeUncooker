#include "VolumeExporterEditor.h"
#include "VolumeExporterEditorWidget.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "GameFramework/Volume.h"
#include "Engine/Selection.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Engine/BrushBuilder.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "Engine/Polys.h"
#include "Engine/Model.h"
#include "Builders/CubeBuilder.h"

void UVolumeExporterEditor::InitializeTheWidget()
{
    if (EditorWidget)
    {
        EditorWidget->OnExportButtonPressedDelegate.BindUObject(this, &UVolumeExporterEditor::OnExportButtonPressed);
        EditorWidget->OnImportButtonPressedDelegate.BindUObject(this, &UVolumeExporterEditor::OnImportButtonPressed);
    }
}

void UVolumeExporterEditor::OnExportButtonPressed()
{
    TArray<AActor*> SelectedActors;
    GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActors);

    TArray<TSharedPtr<FJsonValue>> VolumesJsonArray;

    for (AActor* Actor : SelectedActors)
    {
        AVolume* Volume = Cast<AVolume>(Actor);
        if (Volume && Volume->BrushComponent)
        {
            TSharedPtr<FJsonObject> VolumeObject = MakeShareable(new FJsonObject());
            
            FVector Location = Volume->GetActorLocation();
            FRotator Rotation = Volume->GetActorRotation();
            FVector Scale = Volume->GetActorScale3D();
            FVector BoxExtent = Volume->GetBrushComponent()->Bounds.BoxExtent;

            VolumeObject->SetStringField("Location", Location.ToString());
            VolumeObject->SetStringField("Rotation", Rotation.ToString());
            VolumeObject->SetStringField("Scale", Scale.ToString());
            VolumeObject->SetStringField("BoxExtent", BoxExtent.ToString());

            VolumesJsonArray.Add(MakeShareable(new FJsonValueObject(VolumeObject)));
        }
    }

    if (VolumesJsonArray.Num() > 0)
    {
        TSharedPtr<FJsonObject> RootObject = MakeShareable(new FJsonObject());
        RootObject->SetArrayField("volumes", VolumesJsonArray);

        FString OutputString;
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(RootObject.ToSharedRef(), Writer);

        IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
        if (DesktopPlatform)
        {
            TArray<FString> OutFiles;
            bool bSaved = DesktopPlatform->SaveFileDialog(
                GEditor->GetEditorSubsystem<UEditorEngine>()->GetEditorMainWindow()->GetNativeWindow()->GetOSWindowHandle(),
                TEXT("Export Volumes"),
                FString(""),
                TEXT("volumes.json"),
                TEXT("JSON Files|*.json"),
                EFileDialogFlags::None,
                OutFiles
            );

            if (bSaved && OutFiles.Num() > 0)
            {
                FFileHelper::SaveStringToFile(OutputString, *OutFiles[0]);
            }
        }
    }
}

void UVolumeExporterEditor::OnImportButtonPressed()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        TArray<FString> OutFiles;
        bool bOpened = DesktopPlatform->OpenFileDialog(
            GEditor->GetEditorSubsystem<UEditorEngine>()->GetEditorMainWindow()->GetNativeWindow()->GetOSWindowHandle(),
            TEXT("Import Volumes"),
            FString(""),
            TEXT(""),
            TEXT("JSON Files|*.json"),
            EFileDialogFlags::None,
            OutFiles
        );

        if (bOpened && OutFiles.Num() > 0)
        {
            FString FileContent;
            if (FFileHelper::LoadFileToString(FileContent, *OutFiles[0]))
            {
                TSharedPtr<FJsonObject> JsonObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContent);

                if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
                {
                    const TArray<TSharedPtr<FJsonValue>>* VolumesJsonArray;
                    if (JsonObject->TryGetArrayField("volumes", VolumesJsonArray))
                    {
                        UWorld* World = GEditor->GetEditorWorldContext().World();
                        if (World)
                        {
                            for (const TSharedPtr<FJsonValue>& Value : *VolumesJsonArray)
                            {
                                const TSharedPtr<FJsonObject>& VolumeObject = Value->AsObject();
                                if (VolumeObject.IsValid())
                                {
                                    AVolume* NewVolume = World->SpawnActor<AVolume>();
                                    if (NewVolume)
                                    {
                                        FVector Location, Scale, BoxExtent;
                                        FRotator Rotation;

                                        Location.InitFromString(VolumeObject->GetStringField("Location"));
                                        Rotation.InitFromString(VolumeObject->GetStringField("Rotation"));
                                        Scale.InitFromString(VolumeObject->GetStringField("Scale"));
                                        BoxExtent.InitFromString(VolumeObject->GetStringField("BoxExtent"));

                                        NewVolume->SetActorLocationAndRotation(Location, Rotation);
                                        NewVolume->SetActorScale3D(Scale);
                                        
                                        UCubeBuilder* CubeBuilder = NewObject<UCubeBuilder>();
                                        CubeBuilder->X = BoxExtent.X * 2.0f;
                                        CubeBuilder->Y = BoxExtent.Y * 2.0f;
                                        CubeBuilder->Z = BoxExtent.Z * 2.0f;
                                        
                                        NewVolume->BrushBuilder = CubeBuilder;
                                        NewVolume->Brush = NewObject<UModel>(NewVolume, NAME_None, RF_Transactional);
                                        NewVolume->Brush->Initialize(nullptr, true);
                                        NewVolume->Brush->Polys = NewObject<UPolys>(NewVolume->Brush, NAME_None, RF_Transactional);
                                        NewVolume->GetBrushComponent()->Brush = NewVolume->Brush;
                                        
                                        GUnrealEd->Exec(World, TEXT("BRUSH REBUILD"));
                                        NewVolume->PostEditChange();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}