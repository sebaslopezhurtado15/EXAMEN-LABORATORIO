# EXAMEN DE LABORATORIO — SIS457 - Grupo 4

Proyecto desarrollado en Unreal Engine 4.27.2 utilizando C++.

El examen implementa un miniescenario rectangular tipo pinball dentro del proyecto `AventuraUSFX022026L4`. El Pawn se utiliza como una plataforma controlada por el jugador, el proyectil se convierte en una pelota que rebota indefinidamente y se generan plataformas destructibles e indestructibles de forma aleatoria.

---

## 1. Objetivo del proyecto

Desarrollar el examen de laboratorio aplicando conceptos de C++ y Unreal Engine 4.27.2, utilizando:

* `APawn`.
* `AActor`.
* Herencia.
* `UStaticMeshComponent`.
* `UProjectileMovementComponent`.
* `TArray`.
* `FVector`.
* `FMath::RandRange`.
* `SpawnActor()`.
* `OnComponentHit`.
* `AddDynamic`.
* Perfiles de colisión.
* `BlockAll`.
* `Destroy()`.
* `DefaultPawnClass`.
* Materiales para diferenciar los objetos.

---

## 2. Funcionalidades implementadas

El examen cumple con las siguientes funcionalidades:

1. Se construyó un miniescenario rectangular donde se encuentran el Pawn, un enemigo y las plataformas.
2. El Pawn cambió su apariencia para funcionar visualmente como una plataforma.
3. El movimiento del Pawn está limitado únicamente de izquierda a derecha.
4. El Pawn continúa utilizando `FireShot()` para generar el proyectil mediante `SpawnActor()`.
5. El proyectil fue modificado para funcionar como una pelota que rebota dentro del escenario.
6. La pelota ya no se destruye al impactar y su tiempo de vida es ilimitado.
7. Se generan aleatoriamente entre 5 y 20 plataformas.
8. Las plataformas generadas pueden ser destructibles o indestructibles.
9. `APlataformaDestructible` y `APlataformaIndestructible` heredan de `APlataforma`.
10. Las plataformas destructibles utilizan color rojo y se eliminan cuando son golpeadas por la pelota.
11. Las plataformas indestructibles utilizan color azul y hacen rebotar la pelota sin destruirse.
12. Las posiciones y el tipo de cada plataforma se seleccionan aleatoriamente durante la ejecución.

---

## 3. Pawn

La clase `AAventuraUSFX022026L4Pawn` hereda de `APawn` y fue modificada para representar una plataforma controlada por el jugador.

La apariencia original fue reemplazada por una malla cúbica:

```cpp
StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'
```

También se asignó un material negro:

```cpp
Material'/Game/MaterialesPaintball/M_PawNegra.M_PawNegra'
```

La escala utilizada permite darle una forma similar a una plataforma:

```cpp
ShipMeshComponent->SetRelativeScale3D(FVector(0.5f, 2.5f, 0.5f));
```

El movimiento fue restringido únicamente al eje horizontal utilizando `MoveRight`:

```cpp
const float RightValue = GetInputAxisValue(MoveRightBinding);
const FVector MoveDirection = FVector(0.0f, RightValue, 0.0f);
```

De esta forma, las entradas `W` y `S` ya no modifican el desplazamiento del Pawn durante el juego.

---

## 4. Pelota y rebote

La clase `AAventuraUSFX022026L4Projectile` representa la pelota utilizada en el miniescenario.

Su movimiento continúa utilizando un:

```cpp
UProjectileMovementComponent
```

Para permitir el rebote se configuró:

```cpp
ProjectileMovement->bShouldBounce = true;
ProjectileMovement->Bounciness = 1.0f;
```

La gravedad fue desactivada:

```cpp
ProjectileMovement->ProjectileGravityScale = 0.0f;
```

También se restringió el movimiento al plano del escenario:

```cpp
ProjectileMovement->bConstrainToPlane = true;
ProjectileMovement->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
```

Para evitar que la pelota desaparezca automáticamente se utiliza:

```cpp
InitialLifeSpan = 0.0f;
```

La llamada original a:

```cpp
Destroy();
```

fue deshabilitada dentro de `OnHit()`. De esta forma la pelota permanece activa y continúa rebotando dentro del escenario.

---

## 5. Plataforma destructible

La clase:

```cpp
APlataformaDestructible
```

hereda directamente de:

```cpp
APlataforma
```

Utiliza una malla cúbica y un material rojo:

```cpp
Material'/Game/MaterialesPaintball/M_PlataformaRoja.M_PlataformaRoja'
```

Su colisión utiliza:

```cpp
mallaPlataforma->SetCollisionProfileName(TEXT("BlockAll"));
```

El evento de impacto se conecta mediante:

```cpp
mallaPlataforma->OnComponentHit.AddDynamic(
    this,
    &APlataformaDestructible::AlRecibirImpacto
);
```

Dentro de `AlRecibirImpacto()` se comprueba si el objeto que produjo la colisión utiliza el perfil `Projectile`.

Cuando la pelota golpea la plataforma se ejecuta:

```cpp
Destroy();
```

y la plataforma desaparece del escenario.

---

## 6. Plataforma indestructible

La clase:

```cpp
APlataformaIndestructible
```

también hereda de:

```cpp
APlataforma
```

Utiliza una malla cúbica y un material azul:

```cpp
Material'/Game/MaterialesPaintball/M_PlataformaAzul.M_PlataformaAzul'
```

Su perfil de colisión es:

```cpp
mallaPlataforma->SetCollisionProfileName(TEXT("BlockAll"));
```

La plataforma no ejecuta `Destroy()` cuando recibe un impacto.

Por esta razón, al chocar contra ella la pelota utiliza su configuración de rebote y continúa desplazándose por el escenario.

---

## 7. GameMode y generación aleatoria

La clase `AAventuraUSFX022026L4GameMode` administra la creación de las plataformas del examen.

El Pawn principal se configura mediante:

```cpp
DefaultPawnClass = AAventuraUSFX022026L4Pawn::StaticClass();
```

Las plataformas se almacenan dentro de:

```cpp
TArray<APlataforma*> aPlataformas;
```

Primero se construye un `TArray<FVector>` con posiciones disponibles dentro del miniescenario.

Después se selecciona una cantidad aleatoria:

```cpp
int CantidadPlataformas = FMath::RandRange(5, 20);
```

Para cada plataforma se selecciona aleatoriamente:

* Una posición disponible.
* El tipo de plataforma.

El tipo se determina mediante:

```cpp
int TipoAleatorio = FMath::RandRange(0, 1);
```

Si el resultado es `0`, se genera una plataforma indestructible:

```cpp
World->SpawnActor<APlataformaIndestructible>();
```

Si el resultado es `1`, se genera una plataforma destructible:

```cpp
World->SpawnActor<APlataformaDestructible>();
```

Después de utilizar una posición se elimina del arreglo mediante:

```cpp
PosicionesDisponibles.RemoveAt(IndiceAleatorio);
```

Esto evita que dos plataformas sean generadas exactamente en la misma posición.

---

## 8. Funcionamiento

```text
Inicio
  |
  v
Miniescenario rectangular
  |
  +-------------------------+
  |                         |
  v                         v
Pawn                    GameMode
  |                         |
  |                         v
  |                Cantidad aleatoria
  |                    entre 5 y 20
  |                         |
  |                         v
  |                Crear plataformas
  |                         |
  |              +----------+----------+
  |              |                     |
  |              v                     v
  |       Indestructible          Destructible
  |          azul                    roja
  |              |                     |
  |              |                     |
  v              |                     |
Mover izquierda  |                     |
y derecha        |                     |
  |              |                     |
  v              |                     |
Disparar pelota  |                     |
  |              |                     |
  v              v                     v
Pelota rebota --------> Rebota      Impacto
indefinidamente                         |
                                       v
                                   Destroy()
```

---

## 9. Controles

Movimiento del Pawn:

* `A` → mover hacia la izquierda.
* `D` → mover hacia la derecha.
* `Gamepad Left X` → movimiento horizontal.

Dirección del disparo:

* Flecha arriba.
* Flecha abajo.
* Flecha izquierda.
* Flecha derecha.
* `Gamepad Right Stick`.

---

## 10. Archivos principales

```text
Source/AventuraUSFX022026L4/
│
├── AventuraUSFX022026L4GameMode.h
├── AventuraUSFX022026L4GameMode.cpp
│
├── AventuraUSFX022026L4Pawn.h
├── AventuraUSFX022026L4Pawn.cpp
│
├── AventuraUSFX022026L4Projectile.h
├── AventuraUSFX022026L4Projectile.cpp
│
├── Plataforma.h
├── Plataforma.cpp
│
├── PlataformaDestructible.h
├── PlataformaDestructible.cpp
│
├── PlataformaIndestructible.h
└── PlataformaIndestructible.cpp
```

---

## 11. Conceptos utilizados

En el examen se aplicaron conceptos de Programación Orientada a Objetos:

* Herencia: `APlataformaDestructible` y `APlataformaIndestructible` heredan de `APlataforma`.
* Clases y objetos: se utilizan clases diferentes para representar al Pawn, la pelota y las plataformas.
* Métodos: `FireShot()`, `OnHit()` y `AlRecibirImpacto()`.
* Punteros: las plataformas se almacenan mediante `APlataforma*`.
* Polimorfismo: el `TArray<APlataforma*>` puede almacenar objetos de las clases hijas destructible e indestructible.

También se utilizaron elementos propios de Unreal Engine como:

* `UStaticMeshComponent`.
* `UProjectileMovementComponent`.
* `TArray`.
* `FVector`.
* `FMath::RandRange`.
* `SpawnActor()`.
* `OnComponentHit`.
* `AddDynamic`.
* `Destroy()`.
* `DefaultPawnClass`.

---

## 12. Tecnologías utilizadas

* C++.
* Unreal Engine 4.27.2.
* Visual Studio.
* Git.
* GitHub.
* Git LFS.

---

## 13. Ejecución

1. Abrir `AventuraUSFX022026L4.uproject` con Unreal Engine 4.27.2.
2. Compilar el código C++.
3. Ejecutar el nivel.
4. Comprobar que el Pawn posee apariencia de plataforma.
5. Mover el Pawn únicamente de izquierda a derecha.
6. Disparar la pelota utilizando las flechas de dirección.
7. Comprobar que la pelota continúa rebotando sin destruirse.
8. Observar que se generan aleatoriamente entre 5 y 20 plataformas.
9. Comprobar que las plataformas azules permanecen después del impacto.
10. Comprobar que las plataformas rojas desaparecen cuando son golpeadas por la pelota.

---

## 14. Resultado

Al ejecutar el proyecto se obtiene un miniescenario rectangular tipo pinball.

El Pawn se desplaza únicamente de izquierda a derecha y puede lanzar una pelota en diferentes direcciones.

La pelota permanece activa y rebota continuamente dentro del escenario. Las plataformas indestructibles de color azul permanecen en el nivel y producen el rebote de la pelota, mientras que las plataformas destructibles de color rojo desaparecen cuando reciben un impacto.

En cada ejecución se genera aleatoriamente una cantidad de entre 5 y 20 plataformas, utilizando posiciones disponibles dentro del miniescenario.

---

## 15. Repositorio

https://github.com/sebaslopezhurtado15/EXAMEN-LABORATORIO/tree/master

---

## 16. Video

Enlace al video explicativo:

`Agregar enlace del video aquí`
