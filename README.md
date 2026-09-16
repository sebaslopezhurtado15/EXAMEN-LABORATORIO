EXAMEN DE LABORATORIO GRUPO 4 - SIS457

Repositorio GitHub:

https://github.com/sebaslopezhurtado15/EXAMEN-LABORATORIO/tree/master

Descripción:

Se desarrolló el Examen de Laboratorio del Grupo 4 de la materia SIS457 tomando como base el proyecto `AventuraUSFX022026L4` y trabajando con C++ en Unreal Engine 4.27.2.

Se construyó un miniescenario rectangular para mantener dentro del área de juego al Pawn, un enemigo, la pelota y las diferentes plataformas.

El comportamiento del Pawn fue modificado para que tenga una apariencia similar a una plataforma. Para ello se utiliza un `UStaticMeshComponent` con una malla cúbica y un material de color negro. Además, su movimiento fue restringido únicamente al eje horizontal, permitiendo desplazarse de izquierda a derecha dentro del escenario.

El Pawn mantiene la capacidad de disparar utilizando `FireShot()`. Al realizar un disparo se genera un objeto de la clase `AAventuraUSFX022026L4Projectile` mediante `SpawnActor()`.

El proyectil fue modificado para funcionar como una pelota que permanece dentro del escenario. Para su movimiento se utiliza un `UProjectileMovementComponent` configurado con rebote mediante `bShouldBounce = true` y `Bounciness = 1.0f`. También se eliminó la gravedad, se restringió el movimiento al plano del escenario y se estableció `InitialLifeSpan = 0.0f`, evitando que la pelota se destruya automáticamente. La llamada a `Destroy()` del proyectil al producirse una colisión también fue deshabilitada, permitiendo que continúe rebotando indefinidamente.

Se crearon las clases `APlataformaDestructible` y `APlataformaIndestructible`, ambas heredadas de la clase padre `APlataforma`.

La clase `APlataformaIndestructible` utiliza una malla cúbica, un material de color azul y el perfil de colisión `BlockAll`. Cuando la pelota impacta contra esta plataforma, la colisión produce el rebote y la plataforma permanece en el escenario.

La clase `APlataformaDestructible` utiliza una malla cúbica y un material de color rojo. Mediante el evento `OnComponentHit` se ejecuta la función `AlRecibirImpacto()`. Esta función comprueba si el componente que produjo la colisión utiliza el perfil `Projectile` y, cuando se cumple esta condición, la plataforma se elimina utilizando `Destroy()`.

En el `GameMode` se utiliza un `TArray<APlataforma*>` para almacenar las plataformas creadas durante la ejecución. Al comenzar el juego se genera una cantidad aleatoria de entre 5 y 20 plataformas mediante `FMath::RandRange(5, 20)`.

Para cada plataforma se selecciona aleatoriamente si será destructible o indestructible y posteriormente se crea utilizando `SpawnActor()`. También se utiliza un `TArray<FVector>` con posiciones disponibles dentro del miniescenario. Después de utilizar una posición, esta se elimina del arreglo mediante `RemoveAt()`, evitando generar dos plataformas en la misma ubicación.

El `GameMode` configura `AAventuraUSFX022026L4Pawn` como Pawn principal mediante `DefaultPawnClass`.

Controles:

- `A` y `D`: mover el Pawn de izquierda a derecha.
- Flechas de dirección: definir la dirección del disparo de la pelota.
- También se mantienen disponibles los controles equivalentes mediante gamepad configurados en el proyecto.

Clases principales utilizadas:

- `AAventuraUSFX022026L4GameMode`
- `AAventuraUSFX022026L4Pawn`
- `AAventuraUSFX022026L4Projectile`
- `APlataforma`
- `APlataformaDestructible`
- `APlataformaIndestructible`

Funcionamiento esperado:

Al iniciar el nivel se genera aleatoriamente una cantidad de entre 5 y 20 plataformas dentro del miniescenario. Las plataformas pueden ser rojas destructibles o azules indestructibles.

El Pawn puede desplazarse solamente de izquierda a derecha y lanzar una pelota. La pelota permanece activa dentro del escenario y rebota continuamente contra las superficies y las plataformas indestructibles.

Cuando la pelota impacta una plataforma destructible, esta detecta la colisión y se elimina del escenario. Las plataformas indestructibles permanecen activas y continúan haciendo rebotar la pelota.

De esta manera se implementan los requisitos principales del examen utilizando herencia, `TArray`, `FVector`, `FMath::RandRange`, `SpawnActor()`, `Destroy()`, eventos de colisión y componentes de movimiento de Unreal Engine 4.27.2.

Tecnologías utilizadas:

- C++
- Unreal Engine 4.27.2
- Visual Studio
- Git
- GitHub

Autor:

Grupo 4 - SIS457
