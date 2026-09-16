// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaDestructible.h"
//Pimball
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"

APlataformaDestructible::APlataformaDestructible()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlataformaMeshAsset(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")
	);

	if (PlataformaMeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
		mallaPlataforma->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialRojo(
		TEXT("Material'/Game/MaterialesPaintball/M_PlataformaRoja.M_PlataformaRoja'")
	);
	if (MaterialRojo.Succeeded())
	{
		mallaPlataforma->SetMaterial(0, MaterialRojo.Object);
	}

	mallaPlataforma->SetCollisionProfileName(TEXT("BlockAll"));

	//conexion de:
	mallaPlataforma->OnComponentHit.AddDynamic(this,&APlataformaDestructible::AlRecibirImpacto);
}

//Paimball
void APlataformaDestructible::AlRecibirImpacto(UPrimitiveComponent* ComponenteGolpeado,AActor* OtroActor,UPrimitiveComponent* OtroComponente,FVector ImpulsoNormal,const FHitResult& Hit)
{
	if (OtroActor != nullptr && OtroComponente != nullptr && OtroComponente->GetCollisionProfileName() == FName("Projectile"))
	{
		Destroy();
	}
}