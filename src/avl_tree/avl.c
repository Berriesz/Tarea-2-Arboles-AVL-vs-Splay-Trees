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