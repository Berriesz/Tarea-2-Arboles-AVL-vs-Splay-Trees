#ifndef AVL_H
#define AVL_H

typedef struct AVLNode {
    unsigned int key;
    struct AVLNode *izq;
    struct AVLNode *der;
    int height;
} AVLNode;

int height(AVLNode *node);
int balanceFactor(AVLNode *node);
void updateHeight(AVLNode *node);

AVLNode* zig(AVLNode *y);
AVLNode* zag(AVLNode *y);

AVLNode* zig_zag(AVLNode *z);
AVLNode* zag_zig(AVLNode *z);

AVLNode* balance(AVLNode *node);
AVLNode* insert(AVLNode *node, unsigned int key);
int search(AVLNode *node, unsigned int key);





#endif