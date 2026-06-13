

typedef struct AVLNode {
    unsigned int key;
    struct AVLNode *izq;
    struct AVLNode *der;
    int height;
} AVLNode