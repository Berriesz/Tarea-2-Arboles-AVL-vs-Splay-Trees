#ifndef SPLAY_H
#define SPLAY_H

typedef struct SPLAYNode {
    unsigned int key;
    struct SPLAYNode *izq;
    struct SPLAYNode *der;
    int height;
} SPLAYNode;

int height_splay(SPLAYNode *node);

void updateHeight_splay(SPLAYNode *node);

SPLAYNode* zig_splay(SPLAYNode *y);

SPLAYNode* zag_splay(SPLAYNode *y);

SPLAYNode* zig_zag_splay(SPLAYNode *z);

SPLAYNode* zag_zig_splay(SPLAYNode *z);

SPLAYNode* zig_zig_splay(SPLAYNode *z);

SPLAYNode* zag_zag_splay(SPLAYNode *z);

SPLAYNode* splay(SPLAYNode* root, unsigned int key);

SPLAYNode* insertBST(SPLAYNode* root,
                     unsigned int key);

SPLAYNode* insert_splay(SPLAYNode* root,
                  unsigned int key);

SPLAYNode* search_splay(SPLAYNode* root,
                  unsigned int key,
                  int* found);

void freeSplay(SPLAYNode* root);
#endif