# Librería Genérica de Grafos en C++

Librería modular "incluir y usar" diseñada para la manipulación eficiente de grafos mediante **Listas de Adyacencia** y **Matriz de Adyacencia** en C++. 

## Características Principales
* **Genérica (Templates):** Permite almacenar cualquier tipo de dato (`int`, `string`, objetos personalizados).
* **Resistente a fallos:** Control riguroso de desbordamientos de memoria (`overflow`), validación de índices inexistentes (`out of index`) y liberación segura mediante destructores personalizados.
* **Sin Vectores:** Implementación estricta utilizando exclusivamente memoria dinámica y punteros puros.
* **Algoritmos incluidos:** 
  * Recorrido en Anchura (BFS)
  * Recorrido en Profundidad (DFS)
  * Algoritmo de Camino Más Corto (Dijkstra)

## Compilación y Ejecución
Para compilar desde la terminal situándose en la carpeta raíz:

```bash
g++ src/main.cpp -o bin/programa_grafos
./bin/programa_grafos