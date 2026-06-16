#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Retorna la altura de un nodo.
 */
int height_splay(SPLAYNode *node) {
    if (node == NULL){
        return -1;
    }
    return node->height;
}

/**
 * Recalcula la altura de un nodo a partir de las
 * alturas de sus hijos izquierdo y derecho.
 *
 * height(node) = 1 + max(height(izq), height(der))
 */
void updateHeight_splay(SPLAYNode *node) {
    int hl = height_splay(node->izq);
    int hr = height_splay(node->der);
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
SPLAYNode* zig_splay(SPLAYNode *y) {
    SPLAYNode *x = y->izq;
    SPLAYNode *B = x->der;

    x->der = y;
    y->izq = B;

    updateHeight_splay(y);
    updateHeight_splay(x);

    return x;
}

/**
 * Rotación Zag (simple a la izquierda).
 * y(A, x(B,C)) -> x(y(A,B), C)
 * Recibe la raíz del subárbol desbalanceado (y) y retorna la nueva raíz (x).
 */
SPLAYNode* zag_splay(SPLAYNode *y) {
    SPLAYNode *x = y->der;
    SPLAYNode *B = x->izq;

    x->izq = y;
    y->der = B;

    updateHeight_splay(y);
    updateHeight_splay(x);

    return x;
}

/**
 * Rotación doble Zig-Zag (caso Izquierda-Derecha).
 * z(y(A, x(B,C)), D) -> x(y(A,B), z(C,D))
 * Primero zag sobre el hijo izquierdo, luego zig sobre z.
 */
SPLAYNode* zig_zag_splay(SPLAYNode *z) {
    z->izq = zag_splay(z->izq);
    return zig_splay(z);
}

/**
 * Rotación doble Zag-Zig (caso Derecha-Izquierda).
 * z(A, y(x(B,C), D)) -> x(z(A,B), y(C,D))
 * Primero zig sobre el hijo derecho, luego zag sobre z.
 */
SPLAYNode* zag_zig_splay(SPLAYNode *z) {
    z->der = zig_splay(z->der);
    return zag_splay(z);
}

/**
 * Rotación doble Zig-Zig (caso Izquierda-Izquierda).
 * z(y(x(A,B), C), D) -> x(A, y(B, z(C,D)))
 * Primero zig sobre z, luego zig sobre la nueva raíz.
 */
SPLAYNode* zig_zig_splay(SPLAYNode *z) {
    z = zig_splay(z);
    return zig_splay(z);
}

/**
 * Rotación doble Zag-Zag (caso Derecha-Derecha).
 * z(A, y(B, x(C,D))) -> x(z(A,B), y(C,D))
 * Primero zag sobre z, luego zag sobre la nueva raíz.
 */
SPLAYNode* zag_zag(SPLAYNode *z) {
    z = zag_splay(z);
    return zag_splay(z);
}

/**
 * Lleva a la raíz el nodo con clave key mediante una secuencia
 * de rotaciones tipo Zig, Zag, Zig-Zig, Zag-Zag, Zig-Zag o Zag-Zig.
 *
 * Si la clave no existe en el árbol, lleva a la raíz el último
 * nodo visitado durante la búsqueda.
 *
 * Retorna la nueva raíz del subárbol.
 */
SPLAYNode* splay(SPLAYNode* root, unsigned int key) {

    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        if (root->izq == NULL) {
            return root;
        }

        // Zig-Zig
        if (key < root->izq->key) {
            root->izq->izq = splay(root->izq->izq, key);
            root = zig_splay(root);
        }

        // Zig-Zag
        else if (key > root->izq->key) {
            root->izq->der = splay(root->izq->der, key);
            if (root->izq->der != NULL) {
                root->izq = zag_splay(root->izq);
            }
        }

        if (root->izq == NULL) {
            return root;
        }
        return zig_splay(root);
    }

    else {
        if (root->der == NULL) {
            return root;
        }

        // Zag-Zag
        if (key > root->der->key) {
            root->der->der = splay(root->der->der, key);
            root = zag_splay(root);
        }

        // Zag-Zig
        else if (key < root->der->key) {
            root->der->izq = splay(root->der->izq, key);
            if (root->der->izq != NULL) {
                root->der = zig_splay(root->der);
            }
        }

        if (root->der == NULL) {
            return root;
        }

        return zag_splay(root);
    }
}

/**
 * Busca la clave key en el árbol.
 *
 * Independientemente de si la clave existe o no,
 * ejecuta una operación splay para llevar a la raíz
 * el nodo encontrado o el último nodo visitado.
 *
 * Retorna true si la clave existe en el árbol.
 */
SPLAYNode* search_splay(
        SPLAYNode* root,
        unsigned int key,
        int* found
){

    root = splay(root,key);

    *found =
       (root != NULL &&
        root->key == key);

    return root;
}

/**
 * Inserta una nueva clave siguiendo las reglas de un
 * Árbol Binario de Búsqueda (ABB/BST) tradicional.
 *
 * No realiza operaciones de splay.
 *
 * Retorna la raíz actualizada del subárbol.
 */
SPLAYNode* insertBST(SPLAYNode* root, unsigned int key) {

    if (root == NULL) {
        SPLAYNode* nuevo = (SPLAYNode*) malloc(sizeof(SPLAYNode));
        nuevo->key = key;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        nuevo->height = 0;
        return nuevo;
    }

    if (key <= root->key) {
        root->izq = insertBST(root->izq, key);
    }
    else {
        root->der = insertBST(root->der, key);
    }

    updateHeight_splay(root);

    return root;
}

/**
 * Inserta una nueva clave en el árbol.
 *
 * Primero realiza una inserción ABB tradicional
 * y luego ejecuta splay sobre la clave insertada,
 * dejándola en la raíz del árbol.
 *
 * Retorna la nueva raíz.
 */
SPLAYNode* insert_splay(SPLAYNode* root, unsigned int key) {

    root = insertBST(root, key);

    root = splay(root, key);

    return root;
}

void freeSplay(SPLAYNode* root)
{
    if(root==NULL)
        return;

    freeSplay(root->izq);

    freeSplay(root->der);

    free(root);
}