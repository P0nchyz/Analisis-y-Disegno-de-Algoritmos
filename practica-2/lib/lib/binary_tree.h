#ifndef BINARY_TREE_H
#define BINARY_TREE_H

// Estructura de Nodo
struct Nodo {
    int dato;
    struct Nodo* izq;
    struct Nodo* der;
};

// Función para crear un nuevo nodo
struct Nodo* CrearNodo(int dato);

// Función para insertar un valor en el árbol binario
void Insertar(struct Nodo** raiz, int dato);

// Función para buscar un valor en el árbol binario
bool Encontrado(struct Nodo* raiz, int dato);

#endif // BINARY_TREE_H
