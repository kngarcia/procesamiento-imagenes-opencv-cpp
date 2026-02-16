# Procesamiento de Imágenes con OpenCV en C++

Este repositorio contiene una serie de ejercicios de **procesamiento digital de imágenes** implementados en **C++ usando OpenCV**, donde los algoritmos se desarrollan **de forma manual**, sin utilizar funciones de alto nivel de la librería (por ejemplo, conversiones automáticas de color o filtros predefinidos).

El objetivo principal es **comprender en profundidad cómo funcionan los algoritmos a nivel matemático y computacional**, más allá del uso directo de la API.

---

## 📌 Contenido

Cada ejercicio se encuentra organizado de forma independiente y aborda un concepto fundamental del procesamiento de imágenes:

### 🟢 Ejercicio 1 – Conversión RGB a HSV (manual)
- Conversión píxel a píxel de BGR a HSV.
- Implementación directa de las ecuaciones matemáticas.
- Adaptación al formato HSV utilizado por OpenCV.

### 🟢 Ejercicio 2 – Modificación manual de la saturación
- Conversión BGR → HSV manual.
- Incremento de la componente de saturación.
- Conversión HSV → BGR manual.
- Incluye mensajes de depuración para validación de resultados.

### 🟢 Ejercicio 3 – K-Means manual para cuantización de color
- Implementación completa del algoritmo K-Means desde cero.
- Uso de distancia euclidiana en el espacio RGB.
- Generación de imagen cuantizada y paleta de colores resultante.

### 🟢 Ejercicio 4 – Balance de blancos (Gray World)
- Cálculo de promedios por canal.
- Corrección de color basada en la hipótesis de mundo gris.
- Aplicación de factores de escala por canal.

### 🟢 Ejercicio 6 – Corrección Gamma mediante LUT
- Construcción manual de una Look-Up Table (LUT).
- Aplicación de corrección gamma a cada canal.
- Mejora de brillo y contraste de la imagen.

### 🟢 Ejercicio 7 – Viñeteado (Vignette)
- Atenuación progresiva de la imagen hacia los bordes.
- Cálculo de distancia radial al centro.
- Aplicación de un factor de oscurecimiento dependiente de la distancia.

---

## 🗂️ Estructura del proyecto

