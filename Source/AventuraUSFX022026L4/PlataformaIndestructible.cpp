// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaIndestructible.h"
//Pinball
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"

//Pinball
APlataformaIndestructible::APlataformaIndestructible()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlataformaMeshAsset(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")
	);
	if (PlataformaMeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
		mallaPlataforma->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAzul(
		TEXT("Material'/Game/MaterialesPaintball/M_PlataformaAzul.M_PlataformaAzul'")
	);
	if (MaterialAzul.Succeeded())
	{
		mallaPlataforma->SetMaterial(0, MaterialAzul.Object);
	}
	mallaPlataforma->SetCollisionProfileName(TEXT("BlockAll"));
}

