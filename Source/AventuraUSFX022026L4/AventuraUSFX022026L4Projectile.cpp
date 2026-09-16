// Copyright Epic Games, Inc. All Rights Reserve

#include "AventuraUSFX022026L4Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AAventuraUSFX022026L4Projectile::AAventuraUSFX022026L4Projectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	// Paintball: pelota un poco mas grande
	ProjectileMesh->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));

	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAventuraUSFX022026L4Projectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	//Pimball
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	// Rebote
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;

	// Evita que la pelota se eleve en Z
	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));

	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// destruir 0,0f 
	InitialLifeSpan = 0.0f;
}


void AAventuraUSFX022026L4Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	//mensaje
	UE_LOG(LogTemp, Warning, TEXT("COLISION BLOCK: proyectil golpeo una plataforma"));

	//Destroy();
}