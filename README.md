EXAMEN DE LABORATORIO GRUPO 4 - SIS457

Entorno de trabajo

- **Materia:** SIS457 — USFX
- **Lenguaje:** C++
- **Motor:** Unreal Engine **4.27.2**
- **IDE:** Microsoft Visual Studio
- **Control de versiones:** Git / GitHub

Regla de trabajo

La solución debe ser **simple, directa, funcional, fácil de leer y fácil de defender**.

Si algo ya funciona, no debe cambiarse sin necesidad. Se debe modificar únicamente lo necesario para cumplir el enunciado y mantener compatibilidad estricta con **Unreal Engine 4.27.2**.

Procedimiento para resolver el examen/laboratorio

1. Leer literalmente todo el enunciado.
2. Separar cada requisito.
3. Revisar el código actual antes de modificarlo.
4. Reutilizar código de laboratorios anteriores cuando corresponda.
5. Elegir la solución más simple que cumpla el requisito.
6. Modificar primero las declaraciones necesarias en `.h`.
7. Implementar la lógica correspondiente en `.cpp`.
8. Compilar.
9. Probar dentro de Unreal Engine.
10. Corregir solamente lo que falle.
11. Verificar requisito por requisito antes de entregar.

Estructura básica de una clase de Unreal

Archivo `.h`

Normalmente contiene:

- Declaración de la clase.
- Componentes.
- Variables.
- `UPROPERTY` cuando sea necesario.
- `UFUNCTION` cuando sea necesario.
- Declaración de funciones.

Archivo `.cpp`

Normalmente contiene:

- Constructor.
- `BeginPlay()`.
- `Tick()` cuando el comportamiento necesite actualización continua.
- Implementación de funciones.
- Lógica del comportamiento.

Herramientas simples que se deben preferir

Cuando sean suficientes para cumplir el ejercicio, utilizar:

- Variables simples.
- `if / else`.
- `switch`.
- `for`.
- Funciones sencillas.
- `TArray`.
- `FVector`.
- `FMath`.
- `FTimerHandle` y `SetTimer()`.
- `Tick()`.
- `SpawnActor()`.
- `Destroy()`.
- `SetActorLocation()`.

Evitar arquitecturas o patrones avanzados si el enunciado no los exige.

Ejemplo de movimiento simple de plataformas

Si existen varios movimientos, una solución académicamente sencilla es utilizar una variable entera y un `switch`:

```cpp
switch (TipoMovimiento)
{
case 0:
    // Movimiento 1
    break;

case 1:
    // Movimiento 2
    break;

case 2:
    // Movimiento 3
    break;
}
```

No es necesario crear una clase distinta para cada movimiento si el ejercicio puede resolverse correctamente con esta estructura.

GameMode

Si el `GameMode` ya administra generación de objetos, plataformas, arreglos o temporizadores, se debe mantener esa línea de trabajo.

Elementos válidos y sencillos:

```cpp
TArray<APlataforma*> Plataformas;
FTimerHandle TimerHandle;
```

También pueden utilizarse directamente:

```cpp
SpawnActor();
Destroy();
RemoveAt();
FMath::RandRange();
```

STL — recordatorio rápido

`vector`

```cpp
include <vector>

std::vector<int> numeros;
numeros.push_back(10);
numeros.pop_back();
numeros.size();
numeros.empty();
numeros.clear();
```

`list`

```cpp
include <list>

std::list<int> lista;
lista.push_back(10);
lista.push_front(5);
lista.pop_back();
lista.pop_front();
```

`queue`

```cpp
include <queue>

std::queue<int> cola;
cola.push(10);
cola.front();
cola.back();
cola.pop();
```

`stack`

```cpp
include <stack>

std::stack<int> pila;
pila.push(10);
pila.top();
pila.pop();
```

`map`

```cpp
include <map>
include <string>

std::map<int, std::string> datos;
datos[1] = "Uno";
```

Iteradores

```cpp
for (std::vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
{
    std::cout << *it << std::endl;
}
```

- `begin()` apunta al primer elemento.
- `end()` apunta a la posición posterior al último elemento.
- `*it` obtiene el elemento al que apunta el iterador.

Compilación y comprobación

Después de cada modificación importante:

1. Guardar los archivos.
2. Compilar el proyecto.
3. Confirmar que no existen errores de compilación.
4. Volver a Unreal Engine.
5. Ejecutar con **Play**.
6. Comprobar visualmente el requisito correspondiente.

No se debe considerar terminado un ejercicio solamente porque compile.

Verificación final

Antes de entregar:

```text
REQUISITO 1 -> CUMPLIDO / NO CUMPLIDO
REQUISITO 2 -> CUMPLIDO / NO CUMPLIDO
REQUISITO 3 -> CUMPLIDO / NO CUMPLIDO
REQUISITO 4 -> CUMPLIDO / NO CUMPLIDO
```

Cómo defenderlo ante el docente

La explicación debe ser sencilla y relacionada directamente con el código utilizado.

Ejemplos:

- "Uso un `TArray` para almacenar las plataformas."
- "Uso un `for` para crear los objetos."
- "Uso `Tick()` porque necesito actualizar la posición continuamente."
- "Uso `FVector` para manejar posiciones y direcciones."
- "Uso un `switch` para seleccionar distintos movimientos."
- "Cuando el objeto llega a un límite, cambio el sentido de la dirección."

Regla final

> No buscamos el código más sofisticado. Buscamos el código correcto, simple, funcional, compatible con Unreal Engine 4.27.2 y fácil de explicar durante la defensa.
