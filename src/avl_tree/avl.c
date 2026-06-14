#include "avl.h"
#include <stdio.h>

int height(AVLNode *node) {
    if (node == NULL){
        return -1;
    }
    return node->height;
}

int balanceFactor(AVLNode *node) {
    if (node == NULL){
        return 0;
    }
    return height(node->izq) - height(node->der);
}

void updateHeight(AVLNode *node) {
    int hl = height(node->izq);
    int hr = height(node->der);
    int max_height;
    if(hl > hr) {
        max_height = hl;
    }else {
        max_height = hr;
    }
    node->height = 1 + max_height;
    
}

/**
 * Rotación Zig (simple a la derecha).
 * y(x(A,B), C) -> x(A, y(B,C))
 * Recibe la raíz del subárbol desbalanceado (y) y retorna la nueva raíz (x).
 */
AVLNode* zig(AVLNode *y) {
    AVLNode *x = y->izq;
    AVLNode *B = x->der;

    x->der = y;
    y->izq = B;

    updateHeight(y);
    updateHeight(x);

    return x;
}

/**
 * Rotación Zag (simple a la izquierda).
 * y(A, x(B,C)) -> x(y(A,B), C)
 * Recibe la raíz del subárbol desbalanceado (y) y retorna la nueva raíz (x).
 */
AVLNode* zag(AVLNode *y) {
    AVLNode *x = y->der;
    AVLNode *B = x->izq;

    x->izq = y;
    y->der = B;

    updateHeight(y);
    updateHeight(x);

    return x;
}

/**
 * Rotación doble Zig-Zag (caso Izquierda-Derecha).
 * z(y(A, x(B,C)), D) -> x(y(A,B), z(C,D))
 * Primero zag sobre el hijo izquierdo, luego zig sobre z.
 */
AVLNode* zig_zag(AVLNode *z) {
    z->izq = zag(z->izq);
    return zig(z);
}

/**
 * Rotación doble Zag-Zig (caso Derecha-Izquierda).
 * z(A, y(x(B,C), D)) -> x(z(A,B), y(C,D))
 * Primero zig sobre el hijo derecho, luego zag sobre z.
 */
AVLNode* zag_zig(AVLNode *z) {
    z->der = zig(z->der);
    return zag(z);
}

// BALACEAR Y INSERTAR

/**
 * Balancea un nodo si su Balance Factor es 2 o -2.
 * Identifica el caso (LL, RR, LR, RL) y aplica la rotación correspondiente.
 * Parámetros: node → nodo a balancear
 * Retorna: nueva raíz del subárbol
 */
AVLNode* balance(AVLNode *node) {

    int bf = balanceFactor(node);

    // Caso LL: BF(z) = 2 y BF(hijo izq) >= 0
    if (bf == 2 && balanceFactor(node->izq) >= 0)
        return zig(node);
    // Caso LR: BF(z) = 2 y BF(hijo izq) < 0
    if (bf == 2 && balanceFactor(node->izq) < 0)
        return zig_zag(node);
    // Caso RR: BF(z) = -2 y BF(hijo der) <= 0
    if (bf == -2 && balanceFactor(node->der) <= 0)
        return zag(node);
    // Caso RL: BF(z) = -2 y BF(hijo der) > 0
    if (bf == -2 && balanceFactor(node->der) > 0)
        return zag_zig(node);

    return node; // ya estaba balanceado
}

/**
 * Inserta un nuevo nodo con clave key en el subárbol con raíz node.
 * Parámetros: node → raíz del subárbol, key → clave a insertar
 * Retorna: nueva raíz del subárbol (puede cambiar por rotaciones)
 */
AVLNode* insert(AVLNode *node, unsigned int key) {
    // Caso base
    if (node == NULL) {
        AVLNode *new = (AVLNode*)malloc(sizeof(AVLNode));
        new->key = key;
        new->izq = NULL;
        new->der = NULL;
        new->height = 0;
        return new;
    }

    // recursivo
    if (key < node->key)
        node->izq = insert(node->izq, key);
    else if (key > node->key)
        node->der = insert(node->der, key);
    else
        return node; 

    updateHeight(node);
    return balance(node);
}

