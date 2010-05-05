#include <stdio.h>
#include <stdlib.h>

#include "BinarySortTreeADT.h"

/* 向二叉排序树中加入一个结点 */
int InsertNode(CBSTree *tree, KeyType key)
{
    PCBSTNode p = NULL, parent = NULL;
    PCBSTNode pNewNode = (PCBSTNode)malloc(sizeof(CBSTNode));

    if (NULL == pNewNode) {
        return -1;
    }

    /* 新建结点赋值，特别是左右子结点指针要赋值为NULL */
    pNewNode->m_ktKey = key;
    pNewNode->m_pCBSTNLeft = NULL;
    pNewNode->m_pCBSTNRight = NULL;

    /* 二叉排序树是空树 */
    if (NULL == *tree) {
        *tree = pNewNode;
        return 0;
    } else {
        p = *tree;
        /* 寻找插入位置 */
        while (NULL != p) {
            /* key值已在二叉排序树中 */
            if (p->m_ktKey == key) {
                return 0;
            } else {
                parent = p;
                p = (p->m_ktKey < key) ? p->m_pCBSTNRight : p->m_pCBSTNLeft;
            }
        }

        if (parent->m_ktKey < key) {
            parent->m_pCBSTNRight = pNewNode;
        } else {
            parent->m_pCBSTNLeft = pNewNode;
        }
        return 0;
    }
}

/* 通过值查找并删除一个结点 */
int DelNode(CBSTree * tree, KeyType key)
{
    PCBSTNode p = NULL, q = NULL, parent = NULL, child = NULL;
    p = *tree;
    /* parent为NULL表示根结点的父亲为NULL */
    while (NULL != p) {
        if (p->m_ktKey == key) {
            break;
        } else { 
            parent = p;
            p = (p->m_ktKey < key) ? p->m_pCBSTNRight : p->m_pCBSTNLeft;
        }
    }

    /* p为NULL时， 表示没有找到结点值为key的结点 */
    if (NULL == p) {
        return 0;
    }

    /* p, q现在都是保存了待删结点指针 */
    q = p;

    /* 待删结点有两个儿子结点，进行一下转化 */
    if (NULL != p->m_pCBSTNLeft && NULL != p->m_pCBSTNRight) {
        parent = p;
        p = p->m_pCBSTNRight;
        while (NULL != p->m_pCBSTNLeft) {
            parent = p;
            p = p->m_pCBSTNLeft;
        }
        /* p中保存了待删结点右子树中最左下的结点指针， 
         * parent中就保存了该结点父亲指针 
         * */
        child = p->m_pCBSTNRight;
    }

    /* parent保存待删结点的父亲结点指针， 
     * child保存了待删结点的儿子结点指针（待删结点至多只有一个儿子， 
     * 有两个会转化为0个或1个右结点）
     * */

    /* 待删结点是根结点 */
    if (NULL == parent) {
        *tree = child;
    } else {
        /*待删结点是父亲结点的左儿子*/
        if (parent->m_pCBSTNLeft == p) {
            parent->m_pCBSTNLeft = child;
        } else {
            parent->m_pCBSTNRight = child;
        }
        /*待删结点有两个儿子结点， 转化后需要交换两个结点值 */
        if (p != q) {
            q->m_ktKey = p->m_ktKey;
        }
    }
    free(p);
    return 0;
}

/* 通过值查找结点并返回结点的指针（设为常量指针） */
const CBSTNode *SearchNode(CBSTree * tree, KeyType key)
{
    PCBSTNode p = *tree;
    while (NULL != p) { 
        if (p->m_ktKey == key) {
            break; 
        } else {
            p = (p->m_ktKey < key) ? p->m_pCBSTNRight : p->m_pCBSTNLeft;
        }
    }
    
    return p;
}

/* 中序遍历二叉排序树的结点 */
void PrintAllNodeMid(CBSTree tree)
{
    if (NULL != tree) {
        PrintAllNodeMid(tree->m_pCBSTNLeft);
        printf("%d is accessed.\n", tree->m_ktKey);
        PrintAllNodeMid(tree->m_pCBSTNRight);
    }
}

/* 后序方式释放结点 */
void FreeBSTree(CBSTree tree)
{
    if (NULL != tree) {
        FreeBSTree(tree->m_pCBSTNLeft);
        FreeBSTree(tree->m_pCBSTNRight);
        printf("%d is free.\n", tree->m_ktKey);
        free(tree);
    }
}
