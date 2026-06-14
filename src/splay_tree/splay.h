#ifndef SPLAY_H
#define SPLAY_H

typedef struct SPLAYNode {
    unsigned int key;
    struct SPLAYNode *izq;
    struct SPLAYNode *der;
    int height;
} SPLAYNode;

int height(SPLAYNode *node);

void updateHeight(SPLAYNode *node);

SPLAYNode* zig(SPLAYNode *y);
SPLAYNode* zag(SPLAYNode *y);

SPLAYNode* zig_zag(SPLAYNode *z);
SPLAYNode* zag_zig(SPLAYNode *z);
SPLAYNode* zig_zig(SPLAYNode *z);
SPLAYNode* zag_zag(SPLAYNode *z);



#endif