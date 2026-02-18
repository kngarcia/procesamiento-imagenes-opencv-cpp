# Procesamiento de Imágenes con OpenCV en C++

Este repositorio contiene una serie de ejercicios de **procesamiento digital de imágenes** implementados en **C++ usando OpenCV**, donde los algoritmos se desarrollan **de forma manual**, sin utilizar funciones de alto nivel de la librería (por ejemplo, conversiones automáticas de color o filtros predefinidos).

El objetivo principal es **comprender en profundidad cómo funcionan los algoritmos a nivel matemático y computacional**, más allá del uso directo de la API.

---

## Contenido

Cada ejercicio se encuentra organizado de forma independiente y aborda un concepto fundamental del procesamiento de imágenes:

### Ejercicio 1 – Conversión RGB a HSV (manual)
- Conversión píxel a píxel de BGR a HSV.
- Implementación directa de las ecuaciones matemáticas.
- Adaptación al formato HSV utilizado por OpenCV.

### Ejercicio 2 – Modificación manual de la saturación
- Conversión BGR → HSV manual.
- Incremento de la componente de saturación.
- Conversión HSV → BGR manual.
- Incluye mensajes de depuración para validación de resultados.

### Ejercicio 3 – K-Means manual para cuantización de color
- Implementación completa del algoritmo K-Means desde cero.
- Uso de distancia euclidiana en el espacio RGB.
- Generación de imagen cuantizada y paleta de colores resultante.

### Ejercicio 4 – Balance de blancos (Gray World)
- Cálculo de promedios por canal.
- Corrección de color basada en la hipótesis de mundo gris.
- Aplicación de factores de escala por canal.

### Ejercicio 6 – Corrección Gamma mediante LUT
- Construcción manual de una Look-Up Table (LUT).
- Aplicación de corrección gamma a cada canal.
- Mejora de brillo y contraste de la imagen.

### Ejercicio 7 – Viñeteado (Vignette)
- Atenuación progresiva de la imagen hacia los bordes.
- Cálculo de distancia radial al centro.
- Aplicación de un factor de oscurecimiento dependiente de la distancia.

---

Cada archivo `.cpp` contiene:
- La implementación del ejercicio
- Comentarios explicativos paso a paso
- Un `main()` independiente para facilitar pruebas y depuración

---
## Requisitos

- C++17 o superior
- OpenCV 4.x
- CMake
- Sistema operativo Linux / Windows

---

## Compilación

Desde la raíz del proyecto:

```bash
mkdir build
cd build
cmake ..
make
```

# Motion Analysis with OpenCV (C++)

Este repositorio contiene implementaciones básicas de análisis de movimiento
utilizando OpenCV y C++, desarrolladas con fines académicos y educativos.

Las implementaciones están hechas **desde cero**, usando bucles explícitos
para entender el procesamiento píxel a píxel.

---

## Contenido

### 1. Frame Difference
Archivo: `frame_difference.cpp`

- Compara el frame actual con el frame anterior
- Detecta cambios instantáneos
- No mantiene un modelo de fondo
- Muy sensible al ruido y a cambios de iluminación

---

### 2. Running Average
Archivo: `running_average.cpp`

- Construye un modelo de fondo dinámico
- Usa promedio exponencial con un factor `alpha`
- No detecta movimiento por sí solo
- Se adapta progresivamente a la escena

---

### 3. Background Subtraction (combinado)
Archivo: `background_subtraction.cpp`

- Combina running average + diferencia + umbral
- Permite detectar objetos en movimiento
- Base conceptual de los algoritmos modernos de sustracción de fondo

---

## Requisitos

- C++11 o superior
- OpenCV 4.x
- CMake ≥ 3.10
- Cámara web funcional

---

## Compilación

```bash
mkdir build
cd build
cmake ..
make

