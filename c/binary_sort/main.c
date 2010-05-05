/*
 * gcc -o main main.c BinarySortTreeADT.c
 */

#include <stdio.h>

#include "BinarySortTreeADT.h"

int main(int argc, char *argv[])
{
    CBSTNode rootNode;
    rootNode.m_ktKey = 10;
    rootNode.m_pCBSTNLeft = NULL;
    rootNode.m_pCBSTNRight = NULL;
    
    CBSTree root = &rootNode;

    InsertNode(&root, 5);
    InsertNode(&root, 4);
    InsertNode(&root, 10);
    InsertNode(&root, 25);
    InsertNode(&root, 3);
    InsertNode(&root, 7);
    InsertNode(&root, 9);

    PrintAllNodeMid(root);

    return 0;
}
