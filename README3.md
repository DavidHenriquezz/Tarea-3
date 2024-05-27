# 8 puzzle

## Descripción

Este es un codigo en C que busca resolver el famoso 8 puzzle, mediante diferentes metodos de busqueda, en este caso es DFS y BFS. El objetivo es que los numeros queden en un orden especifico del 1 al 8, dejando un espacio vacio en la esquina superior izquierda

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar Repl.it para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1.- Visita Repl.it.

2.- Crea una cuenta o inicia sesión.

3.- Una vez en el inicio selecciona "New Repl" y elige "Import from GitHub".

4.- Pegar este link = https://github.com/DavidHenriquezz/BusquedaPeliculas

5.- Repl.it clonará el repositorio y te preparará un entorno de ejecución.

6.- Aprete el boton "Run" para que el codigo se ejecute.

## Funcionalidades

### Funcionando correctamente:

- Busqueda por DFS
- Busqueda por BFS

### A mejorar:

- Modificar la interfaz para que sea más amigable.
- Permitir que la persona ingrese en el orden que quiere el puzzle
- Hacer la función "Buscar Mejor Primero"

### Posibles errores:

- Al cambiar el orden de los numeros el programa puede caerse, debido a que supera las iteraciones
- El DFS esta puesto con una profundidad optima para el puzzle dado, pero si este es cambiado puede que no se encuentre solución o que quede corto.

## Ejemplo de uso

**Paso 1: Seleccionar el metodo de busqueda**

Se comienza seleccionando el metodo de busqueda deseado
```
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero(No implementada)
4) Salir
Ingrese su opción:
```

El sistema muestra todas las peliculas mostrando su ID, nombre y año.

**Paso 2.1: Busqueda por Profundidad**

Si se ingreso el numero 1 se buscará la solucion por dfs.

```
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero(No implementada)
4) Salir
Ingrese su opción: 1
--------------------------------------------
Se encontró una solución en 528 iteraciones
--------------------------------------------
Estado Original:
x 2 8 
1 3 4 
6 5 7 

Estado 1:
1 2 8 
x 3 4 
6 5 7 

Estado 2:
1 2 8 
3 x 4 
6 5 7 

Estado 3:
1 2 8 
3 4 x 
6 5 7 

Estado 4:
1 2 x 
3 4 8 
6 5 7 

Estado 5:
1 x 2 
3 4 8 
6 5 7 

Estado 6:
1 4 2 
3 x 8 
6 5 7 

Estado 7:
1 4 2 
3 5 8 
6 x 7 

Estado 8:
1 4 2 
3 5 8 
6 7 x 

Estado 9:
1 4 2 
3 5 x 
6 7 8 

Estado 10:
1 4 2 
3 x 5 
6 7 8 

Estado 11:
1 x 2 
3 4 5 
6 7 8 

Estado 12:
x 1 2 
3 4 5 
6 7 8 

Presione una tecla para continuar...
```
Una vez encontrada se muestra el camino que siguió para llegar al estado final.

**2.2 : Busqueda por Anchura**

Si se ingreso el numero 2 se buscará la solucion por bfs.

```
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero(No implementada)
4) Salir
Ingrese su opción: 2
--------------------------------------------
Se encontró una solución en 1407 iteraciones
--------------------------------------------
Estado Original:
x 2 8 
1 3 4 
6 5 7 

Estado 1:
1 2 8 
x 3 4 
6 5 7 

Estado 2:
1 2 8 
3 x 4 
6 5 7 

Estado 3:
1 2 8 
3 4 x 
6 5 7 

Estado 4:
1 2 x 
3 4 8 
6 5 7 

Estado 5:
1 x 2 
3 4 8 
6 5 7 

Estado 6:
1 4 2 
3 x 8 
6 5 7 

Estado 7:
1 4 2 
3 5 8 
6 x 7 

Estado 8:
1 4 2 
3 5 8 
6 7 x 

Estado 9:
1 4 2 
3 5 x 
6 7 8 

Estado 10:
1 4 2 
3 x 5 
6 7 8 

Estado 11:
1 x 2 
3 4 5 
6 7 8 

Estado 12:
x 1 2 
3 4 5 
6 7 8 

Presione una tecla para continuar...
````
Una vez encontrada se muestra el camino que siguió para llegar al estado final.
