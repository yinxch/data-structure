#include <cstdlib>

//
// Created by 86155 on 2024/7/20.
//
typedef struct {
    // 动态数组基址
    int *elem;
    int tableLen;
} SSTable;

int searchSeq(SSTable ssTable, int key) {
    int i = 0;
    for (; ssTable.elem[i] != key && i < ssTable.tableLen; i++);
    // 查找成功则返回元素下标，失败则返回 -1
    return i == ssTable.tableLen ? -1 : i;
}

int searchSeqWithSentinel(SSTable ssTable, int key) {
    // 0 号位置存放哨兵，数据从下标 1 开始存
    ssTable.elem[0] = key;
    int i = ssTable.tableLen;
    for (; ssTable.elem[i] != key; i--);
    // 查找成功则返回元素下标，失败则返回 0
    return i;
}

int binarySearch(SSTable ssTable, int key) {
    int low = 0, high = ssTable.tableLen - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (ssTable.elem[mid] == key) {
            return mid;
        } else if (ssTable.elem[mid] > key) {
            high = mid - 1;
        } else if (ssTable.elem[mid] < key) {
            low = mid + 1;
        }
    }
    return -1;
}

// 二叉排序树结点
typedef struct BSTNode {
    int key;
    struct BSTNode *lChild, *rChild;
} BSTNode, *BSTree;

// 二叉排序树查找
BSTNode *bstSearch(int key, BSTree t) {
    while (t != nullptr && key != t->key) {
        t = t->key < key ? t->lChild : t->rChild;
    }
    return t;
}

// 二叉排序树的递归实现
BSTNode *bstSearchLoop(int key, BSTree t) {
    while (t != nullptr && key != t->key) {
        t = bstSearchLoop(key, t->key < key ? t->lChild : t->rChild);
    }
    return t;
}

// 二叉排序树的插入
int bstInsert(int k, BSTree &t) {
    if (t == nullptr) {
        t = (BSTree) malloc(sizeof(BSTNode));
        t->key = k;
        t->lChild = t->rChild = nullptr;
        return 1;
    } else if (t->key == k) {
        return 0;
    } else if (k > t->key) {
        return bstInsert(k, t->rChild);
    } else if (k < t->key) {
        return bstInsert(k, t->lChild);
    } else {
        return 0;
    }
}

BSTree createBST(int str[], int n) {
    BSTree t = nullptr;
    for (int i = 0; i < n; i++) {
        bstInsert(str[i], t);
    }
    return t;
}

// 平衡二叉树结点
typedef struct AVLNode {
    // 数据域
    int key;
    // 平衡因子
    int balance;
    struct AVLNode *lChild, *rChild;
} AVLNode, *AVLTree;
