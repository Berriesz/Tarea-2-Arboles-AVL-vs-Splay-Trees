#ifndef AVL_H
#define AVL_H

typedef struct AVLNode {
    unsigned int key;
    struct AVLNode *izq;
    struct AVLNode *der;
    int height;
} AVLNode

int height(AVLNode *node);
int balanceFactor(AVLNode *node);
void updateHeight(AVLNode *node);




#endif