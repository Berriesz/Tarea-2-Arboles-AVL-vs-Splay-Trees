#include "avl.h"

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
    node->height = 1 + (hl > hr ? hl : hr);
}