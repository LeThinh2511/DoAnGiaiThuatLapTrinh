#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "Canh.h"
#include "Matrix.h"
#include "ListCanh.h"

typedef struct Node
{
    int p;
    Node* l;
    Node* r;
    Matrix matrix;
    Canh c;
    ListCanh listCanh;
}Node;

void initNode(Node& node)
{
    node.p = 0;
    node.l = node.r = NULL;
    node.matrix.m = NULL;
    node.matrix.n = 0;
    node.c.d = 0;
    node.c.r = 0;
    node.c.s = 0;
    node.listCanh.head = NULL;
    node.listCanh.count = 0;
}

void detroyNode(Node& root)
{
    if (root.l == NULL && root.r == NULL)
    {
        detroyMatrix(root.matrix);
        detroyListCanh(root.listCanh);
    }
}

void deleteTree(Node& root)
{
    if (root.l == NULL && root.r == NULL)
    {
        detroyNode(root);
    }
    else if(root.l == NULL)
    {
        deleteTree(*root.r);
    }
    else if (root.r == NULL)
    {
        deleteTree(*root.l);
    }
    else
    {
        deleteTree(*root.l);
        deleteTree(*root.r);
    }
}

void detroyTree(Node& root)
{
    detroyMatrix(root.matrix);
    detroyListCanh(root.listCanh);
}

#endif
