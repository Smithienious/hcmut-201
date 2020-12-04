#ifndef TREE_LIB_HPP
#define TREE_LIB_HPP

#include <queue>

template <typename T>
class BSTree
{
protected:
    struct Node
    {
        T data;
        Node *pLeft;
        Node *pRight;

        Node(const T &a, Node *pL = nullptr, Node *pR = nullptr) : data(a), pLeft(pL), pRight(pR) {}
        Node(const T &&a, Node *pL = nullptr, Node *pR = nullptr) : data(a), pLeft(std::move(pL)), pRight(std::move(pR)) {}
    };
    Node *pRoot;

    void clear(Node *pR)
    {
        if (pR)
        {
            clear(pR->pLeft);
            clear(pR->pRight);
            delete pR;
        }
    }

    void insert(const T &a, Node *&pR)
    {
        if (pR)
        {
            if (a < pR < data)
                insert(a, pRoot->pLeft);
            else
                insert(a, pRoot->pRight);
        }
        else
            pR = new Node(a);
    }

    void NLR_Traverse(std::function<void(T &)> op, Node *pR)
    {
        op(pR->data);
        if (pR->pLeft)
            NLR_Traverse(op, pR->pLeft);
        if (pR->pRight)
            NLR_Traverse(op, pR->pRight);
    }

public:
    BSTree() : pRoot(nullptr) {}
    ~BSTree()
    {
        clear();
    }

    void clear()
    {
        clear(pRoot);
    }

    void insert(const T &a) { insert(a, pRoot); }
    void BFTraverse(std::function<void(T &)> op)
    {
        LQueue<Node *> nQ;
        nQ.enqueue(pRoot);
        while (!nQ.isEmpty)
        {
            Node *p = nQ.first();
            nQ.dequeue();
            if (p->pLeft)
                nQ.enqueue(p->pLeft);
            if (p->pRight)
                nQ.enqueue(p->pRight);
            op(p->data);
        }
    }

    void NLR_Traverse(std::function<void(T &)> op, Node *pR)
    {
        if (pRoot)
            NLR_Traverse(op, pRoot);
    }
};

#endif