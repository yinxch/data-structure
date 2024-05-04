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

// 中序线索化
class InThread {
private:
    // 全局变量 pre 指向当前结点的前驱
    ThreadNode *pre;

    // 中序遍历线索二叉树
    void inThread(ThreadTree t) {
        if (t != NULL) {
            inThread(t->lChild);
            visit(t);
            inThread(t->rChild);
        }
    }

    void visit(ThreadNode *q) {
        // 当前结点的左子树为空，建立前驱线索
        if (q->lChild == NULL) {
            q->lChild = pre;
            q->lTag = 1;
        }
        // 前驱结点不为 NULL，并且右子树为空时，为前驱结点建立后继线索
        if (pre != NULL && pre->rChild == NULL) {
            pre->rChild = q;
            pre->rTag = 1;
        }
        pre = q;
    }

public:
    void createInThread(ThreadTree t) {
        // pre 初始化为NULL
        pre = NULL;
        // 非空二叉树才可以线索化
        if (t != NULL) {
            // 中序线索化二叉树
            inThread(t);
            // 处理遍历的最后一个结点
            // 因为中序遍历的最后一个结点的右孩子指针必为空
            // 所以这里可以不用判断 rChild 是否为 NULL，直接将 rTag 设为 1
            if (pre->rChild == NULL)
                pre->rTag = 1;
        }

    }
};

// 先序线索化
class PreThread {
private:
    // 全局变量 pre 指向当前结点的前驱
    ThreadNode *pre;

    // 先序遍历线索二叉树
    void preThread(ThreadTree t) {
        if (t != NULL) {
            visit(t);
            // lChild 不是前驱线索
            if(t->lTag == 0)
                preThread(t->lChild);
            // 这里需要判断 rTag 吗？
            preThread(t->rChild);
        }
    }

    void visit(ThreadNode *q) {
        // 当前结点的左子树为空，建立前驱线索
        if (q->lChild == NULL) {
            q->lChild = pre;
            q->lTag = 1;
        }
        // 前驱结点不为 NULL，并且右子树为空时，为前驱结点建立后继线索
        if (pre != NULL && pre->rChild == NULL) {
            pre->rChild = q;
            pre->rTag = 1;
        }
        pre = q;
    }

public:
    void createPreThread(ThreadTree t) {
        // pre 初始化为NULL
        pre = NULL;
        // 非空二叉树才可以线索化
        if (t != NULL) {
            // 先序线索化二叉树
            preThread(t);
            // 处理遍历的最后一个结点
            // 因为先序遍历的最后一个结点的右孩子指针必为空
            // 所以这里可以不用判断 rChild 是否为 NULL，直接将 rTag 设为 1
            if (pre->rChild == NULL)
                pre->rTag = 1;
        }

    }
};

class PostThread {
private:
    // 全局变量 pre 指向当前结点的前驱
    ThreadNode *pre;

    // 先序遍历线索二叉树
    void postThread(ThreadTree t) {
        if (t != NULL) {
            visit(t);
            postThread(t->rChild);
            postThread(t->lChild);
        }
    }

    void visit(ThreadNode *q) {
        // 当前结点的左子树为空，建立前驱线索
        if (q->lChild == NULL) {
            q->lChild = pre;
            q->lTag = 1;
        }
        // 前驱结点不为 NULL，并且右子树为空时，为前驱结点建立后继线索
        if (pre != NULL && pre->rChild == NULL) {
            pre->rChild = q;
            pre->rTag = 1;
        }
        pre = q;
    }

public:
    void createPostThread(ThreadTree t) {
        // pre 初始化为NULL
        pre = NULL;
        // 非空二叉树才可以线索化
        if (t != NULL) {
            // 先序线索化二叉树
            postThread(t);
            // 处理遍历的最后一个结点
            // 因为先序遍历的最后一个结点的右孩子指针必为空
            // 所以这里可以不用判断 rChild 是否为 NULL，直接将 rTag 设为 1
            if (pre->rChild == NULL)
                pre->rTag = 1;
        }

    }
};

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