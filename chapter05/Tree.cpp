#include <cstdlib>

#define MaxSize 100

struct ElemType {
    int value;
};

// 1 二叉树的顺序存储
typedef struct BiTNode {
    // 数据域
    ElemType data;
    // 左右孩子指针
    struct BiTNode *lChild, *rChild;
} BiTNode, *BiTree;

// 访问结点的方法
void visit(BiTNode *n) {

}

// 先序遍历
void preOrder(BiTree t) {
    // 1 二叉树为空，则什么也不做
    // 2 二叉树非空
    if (t != NULL) {
        // 访问根结点
        visit(t);
        // 遍历左子树
        preOrder(t->lChild);
        // 遍历右子树
        preOrder(t->rChild);
    }
}

// 中序遍历
void inOrder(BiTree t) {
    // 1 二叉树为空，则什么也不做
    // 2 二叉树非空
    if (t != NULL) {
        // 遍历左子树
        preOrder(t->lChild);
        // 访问根结点
        visit(t);
        // 遍历右子树
        preOrder(t->rChild);
    }
}

// 后序遍历
void postOrder(BiTree t) {
    // 1 二叉树为空，则什么也不做
    // 2 二叉树非空
    if (t != NULL) {
        // 遍历左子树
        preOrder(t->lChild);
        // 遍历右子树
        preOrder(t->rChild);
        // 访问根结点
        visit(t);
    }
}

// 后序遍历的应用：求树的深度
int treeDepth(BiTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int l = treeDepth(t->lChild);
        int r = treeDepth(t->rChild);
        return l > r ? l + 1 : r + 1;
    }
}

// 使用中序遍历找到中序前驱
class PreSearch {
public:
    explicit PreSearch(BiTNode *p) : p(p) {}

    BiTNode *findPre(BiTree t) {
        if (t != NULL) {
            // 遍历左子树
            preOrder(t->lChild);
            // 访问根结点
            visit(t);
            // 遍历右子树
            preOrder(t->rChild);
        }
        return final;
    }

private:
    // p 指向目标结点
    BiTNode *p;
    // 指向当前访问结点的前驱
    BiTNode *pre = NULL;
    // 用于记录最终结果
    BiTNode *final = NULL;

    void visit(BiTNode *q) {
        // 当前访问结点刚好是目标结点 p
        if (q == p) {
            // 找到 p 的前驱
            final = pre;
        } else {
            // 访问结束后将pre指向当前访问的结点
            pre = q;
        }
    }

};

// 线索二叉树结点
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lChild, *rChild;
    // 左右线索标志
    int lTag, rTag;
} ThreadNode, *ThreadTree;

int main() {
    // 初始化所有结点标记为空
//    for (int i = 0; i < MaxSize; i++) {
//        t[i].isEmpty = true;
//    }

    // 定义一颗空树
    BiTree root = NULL;

    // 插入根节点
    root = (BiTree) malloc(sizeof(BiTNode));
    root->data = {1};
    root->lChild = NULL;
    root->rChild = NULL;

    // 插入新节点作为根节点的左孩子
    BiTNode *p = (BiTNode *) malloc(sizeof(BiTNode));
    p->data = {2};
    p->lChild = NULL;
    p->rChild = NULL;
    root->lChild = p;


    return 0;
}