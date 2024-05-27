
#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/stack.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include <string.h>
#include <stdbool.h>

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions; //Secuencia de movimientos para llegar al estado
    int visitado; //Se utiliza para marcar los nodos visitados
    int profundidad; // Se utilizara para limitar la busqueda en dfs
    struct State* padre; // padres para posteriormente imprimir el camino
} State;

// Función para imprimir el estado del puzzle
void imprimirEstado(const State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
}
// Funcion para mostrar el camino para llegar al estado objetivo
void mostrar_camino(State* estado_final) {
    int contador = 0;// inicia un contador para contar en cuantos pasos llego al estado final
    State* estado_actual = estado_final;
    List* camino = list_create();// crea una lista para guardar los estados del camino
    while (estado_actual != NULL){
        list_pushFront(camino, estado_actual); //Añade el estado actual al principio de la lista
        estado_actual = (State*)estado_actual->padre;// avanza al estado padre
    }
    while (list_size(camino) > 0){// Mientras la lista no este vacia
        if (contador == 0){
            printf("Estado Original:\n");//primero imprime el estado original
            imprimirEstado(list_popFront(camino));// luego imprime el estado actual
            printf("\n");
        }
        else{
            printf("Estado %d:\n", contador);//imprime el contador
            imprimirEstado(list_popFront(camino));// luego imprime el estado actual
            printf("\n");
        }
        contador++;// aumenta el contador
    }
    
    
}
// Funcion para verificar si se encuentra en el estado final
int finalState(State* estado){
    State estado_final = {
        {{0, 1, 2}, // Primera fila (0 representa espacio vacío)
         {3, 4, 5}, // Segunda fila
         {6, 7, 8}, // Tercera fila
         },  
    };
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (estado->square[i][j] != estado_final.square[i][j]){ // compara si todas sus claves son iguales
                return 0;// no son iguales
            }
        }
    }
    return 1;// se encontro la solucion
}
// Funcion que compara las matrices
int compararSquare(State* estado1, State* estado2) {
    if (estado1 == NULL || estado2 == NULL) return 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado1->square[i][j] != estado2->square[i][j]) { //compara clave por clave
                return 0; // los estados son diferentes
            }
        }
    }
    return 1; // los estados son iguales
}
// Funcion que determina si un movimiento es valido
int move_valid(State *estado, int x, int y){// verifica si el movimiento es valido
    return(x < 3 && x >= 0 && y < 3 && y >= 0);
}
// Funcion que valida si el estado fue visitado o no
int valid_state(List* estados_visitados, State* estado) {
    State* actual = list_first(estados_visitados);
    while (actual != NULL) {
        
        if (compararSquare(actual, estado)) {// compara los estados
            return 0; // el estado ya fue visitado
        }
        actual = list_next(estados_visitados); // avanza al siguiente estado
    }
    return 1; // el esto aun no fue visitado
}
// Funcion que limpia la memoria
void free_actions(State* estado){
    if (estado->actions != NULL){
        list_clean(estado->actions);//limpia la listas de acciones
        free(estado->actions);// livera la memoria
        estado->actions = NULL;// se le asigna NULL a la lista de acciones
    }
}
// Funcion que crea el estado segun corresponda, arriba, abajo, izquierda o derecha
State* transition(State* estado, int movimiento) {
    State* nuevo_estado = (State*)malloc(sizeof(State));
    if (!nuevo_estado) {
        perror("Falla en reservar memoria");
        exit(EXIT_FAILURE);
    }
    memcpy(nuevo_estado, estado, sizeof(State));
    int x = estado->x; //Se copia la variable para que sea mas sencillo su trabajo
    int y = estado->y; //Se copia la variable para que sea mas sencillo su trabajo
    

    switch (movimiento) {
        case 0: // Arriba 
            if (x > 0) {
                nuevo_estado->square[x][y] = nuevo_estado->square[x - 1][y];
                nuevo_estado->square[x - 1][y] = 0;// Se actualiza la posicion nula
                nuevo_estado->x = x - 1; // Se modifica el valor del nulo en x
            } else {//Sino se puede mover 
                free(nuevo_estado);
                return NULL;
            }
            break;
        case 1: // Abajo 
            if (x < 2) {
                nuevo_estado->square[x][y] = nuevo_estado->square[x + 1][y];
                nuevo_estado->square[x + 1][y] = 0;// Se actualiza la posicion nula
                nuevo_estado->x = x + 1;    // Se modifica el valor del nulo en x
            } else { //Sino se puede mover 
                free(nuevo_estado);
                return NULL;
            }
            break;
        case 2: // Izquierda 
            if (y > 0) {
                nuevo_estado->square[x][y] = nuevo_estado->square[x][y - 1];
                nuevo_estado->square[x][y - 1] = 0;// Se actualiza la posicion nula
                nuevo_estado->y = y - 1;    //Se modifica el valor del nulo en Y
            } else {//Sino se puede mover 
                free(nuevo_estado);
                return NULL;
            }
            break;
        case 3: // Derecha 
            if (y < 2) {
                nuevo_estado->square[x][y] = nuevo_estado->square[x][y + 1];
                nuevo_estado->square[x][y + 1] = 0;// Se actualiza la posicion nula
                nuevo_estado->y = y + 1;    //Se modifica el valor del nulo en Y
            } else {//Sino se puede mover 
                free(nuevo_estado);
                return NULL;
            }
            break;
        default:
            free(nuevo_estado);
            return NULL;
    }
    return nuevo_estado;
}
// Funcion que genera todos los estados vecinos del nodo
List* generar_estados_vecinos(State* estado){
    List* estados_vecinos = list_create();
    int acciones[4] = {0, 1, 2, 3};//Se crea un vector con los posibles movimientos
    
    for (int i = 0; i < 4; i++) {
        State* nuevo_estado = transition(estado, acciones[i]);// se crea un estado nuevo segun su movimiento
        if (nuevo_estado != NULL) {
            list_pushBack(estados_vecinos, nuevo_estado);// se agrega a la lista de los nodos adyacentes 
        }
    }
    return estados_vecinos;
}
// Funcion que busca por profundidad
void dfs(State* estado_inicial) {
    if (estado_inicial == NULL) return;
    int iteraciones  = 0;
    int profundidad_max = 13; // profundidad maxima para que no se vuelva infinito
    List* pila = list_create();
    List* visitados = list_create(); // lista para almacenar los estados visitados
    estado_inicial->padre = NULL; // se le asigna NULL al padre del estado inicial
    list_pushFront(pila, estado_inicial);

    while (list_size(pila) > 0) {
        State* estado_actual = (State*)list_popFront(pila);// se elimina el estado actual de la pila
        if (finalState(estado_actual)) {// Si es el estado final 
            printf("--------------------------------------------\n");
            printf("Se encontró una solución en %d iteraciones\n", iteraciones);// se imprime el numero de iteraciones
            printf("--------------------------------------------\n");
            mostrar_camino(estado_actual);// se imprime el camino
            list_clean(pila);// se limpia la pila
            list_clean(visitados);// se limpia la lista de visitados
            return;
        }

        if (!valid_state(visitados, estado_actual)) {// si el estado no es valido se sigue a la siguiente iteracion
            continue;
        }
        if (estado_actual->profundidad >= profundidad_max) {// si la profundidad es mayor a la maxima se sigue a la siguiente iteracion
            continue;
        }
        list_pushBack(visitados, estado_actual);// se agrega el estado actual a la lista de visitados

        List* estados_vecinos = generar_estados_vecinos(estado_actual);// se generan los estados vecinos
        State* estado_vecino = list_first(estados_vecinos);// se obtiene el primer estado vecino

        while (estado_vecino != NULL) {
            if (valid_state(visitados, estado_vecino)) {// si el estado vecino no es valido se sigue a la siguiente iteracion
                 estado_vecino->profundidad = estado_actual->profundidad + 1;// se aumenta la profundidad del estado vecino
                list_pushFront(pila, estado_vecino);// se agrega el estado vecino a la pila
                estado_vecino->padre = (struct State*)estado_actual;// se le asigna el estado actual como padre del estado vecino
            }
            estado_vecino = list_next(estados_vecinos);// se sigue con el siguiente vecino
        }

        list_clean(estados_vecinos);// se limpia la lista de estados vecinos
        iteraciones ++;// se aumenta el numero de iteraciones
    }
    printf("No se encontró una solución\n");// se muestra un mensaje si no se encontro solucion
    list_clean(pila);// se limpia la pila
    list_clean(visitados);// se limpia la lista de visitados
}
// Funcion que busca por amplitud
void bfs(State* estado_inicial) {
    if (estado_inicial == NULL) return;

    List* cola = list_create();
    List* estados_visitados = list_create();// lista para almacenar los estados visitados
    int iteraciones = 0;// numero de iteraciones
    list_pushBack(cola, estado_inicial);
    estado_inicial->visitado = 1;
    estado_inicial->padre = NULL;// se le asigna NULL al padre del estado inicial

    while (list_size(cola) > 0) {
        State* estado_actual = (State*)list_popFront(cola);// se elimina el estado actual de la cola

        if (finalState(estado_actual)) {// Si es el estado final
            printf("--------------------------------------------\n");
            printf("Se encontró una solución en %d iteraciones\n", iteraciones);// se imprime el numero de iteraciones
            printf("--------------------------------------------\n");
            mostrar_camino(estado_actual);// se imprime el camino
            list_clean(estados_visitados);// se limpia la lista de visitados
            list_clean(cola);// se limpia la cola
            return;
        }

        if (!valid_state(estados_visitados, estado_actual)) {// si el estado no es valido se sigue a la siguiente iteracion
            continue;
        }

        list_pushBack(estados_visitados, estado_actual);// se agrega el estado actual a la lista de visitados
        List* estados_vecinos = generar_estados_vecinos(estado_actual);// se generan los estados vecinos
        State* estado_vecino = list_first(estados_vecinos);// se obtiene el primer estado vecino

        while (estado_vecino != NULL) {// se recorre la lista de estados vecinos
            if (valid_state(estados_visitados, estado_vecino)) {// si el estado vecino no es valido se sigue a la siguiente iteracion
                list_pushBack(cola, estado_vecino);// se agrega el estado vecino a la cola
                estado_vecino->padre = (struct State*)estado_actual;// se le asigna el estado actual como padre del estado vecino
            }
            estado_vecino = list_next(estados_vecinos);// se sigue con el siguiente vecino
        }

        list_clean(estados_vecinos);// se limpia la lista de estados vecinos
        iteraciones++;// se aumenta el numero de iteraciones
    }

    list_clean(estados_visitados);// se limpia la lista de visitados
    list_clean(cola);// se limpia la cola
}
int main() {
    // Estado inicial del puzzle
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 1)
    };
    estado_inicial.actions = list_create();
    estado_inicial.profundidad = 0;// se inicializa la profundidad en 0


    // Imprime el estado inicial
    printf("Estado inicial del puzzle:\n");
    imprimirEstado(&estado_inicial);
    
    char opcion;
    do {
        puts("========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");
        
        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Buscar Mejor Primero(No implementada)");// No implementada
        puts("4) Salir");
    
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
    
        switch (opcion) {
        case '1':
          dfs(&estado_inicial);
          break;
        case '2':
          bfs(&estado_inicial);
          break;
        case '3':
          //best_first(estado_inicial);
          break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != '4');

  return 0;
}