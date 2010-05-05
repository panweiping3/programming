#ifndef _BINARYSORTTREEADT_H
#define _BINARYSORTTREEADT_H
/*
*二叉排序树(Binary Sort Tree)又称二叉查找(搜索)树(Binary Search Tree)。
*其定义为：二叉排序树或者是空树，或者是满足如下性质的二叉树：
*1、若它的左子树非空，则左子树上所有结点的值均小于根结点的值；
*2、若它的右子树非空，则右子树上所有结点的值均大于根结点的值；
*3、左、右子树本身又各是一棵二叉排序树。
*上述性质简称二叉排序树性质(BST性质)，故二叉排序树实际上是满足BST性质的二叉树。
*/

/* 声明结点的值的类型 */
typedef int KeyType;

/* 声明结点类型 */
typedef struct CBSTNode {
    KeyType m_ktKey;
    struct CBSTNode * m_pCBSTNLeft;
    struct CBSTNode * m_pCBSTNRight;
} CBSTNode, *PCBSTNode, *CBSTree;

/* 向二叉排序树中加入一个结点 */
extern int InsertNode(CBSTree *, KeyType);

/* 通过值查找并删除一个结点 */
extern int DelNode(CBSTree *, KeyType);

/* 通过值查找结点并返回结点的指针（设为常量指针） */
extern const CBSTNode * SearchNode(CBSTree *, KeyType);

/* 中序遍历二叉排序树的结点 */
extern void PrintAllNodeMid(CBSTree);

/* 后序方式释放结点 */
extern void FreeBSTree(CBSTree);
#endif

