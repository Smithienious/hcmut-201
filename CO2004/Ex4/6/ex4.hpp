#ifndef EX4_HPP
#define EX4_HPP

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node *addRec(Node *root, T value);
    void add(T value);
    // STUDENT ANSWER BEGIN
    // You can define other functions here to help you.

    bool find(T i)
    {
        // TODO: return true if value i is in the tree; otherwise, return false.
    }

    T sum(T l, T r)
    {
        // TODO: return the sum of all element in the tree has value in range [l,r].
    }

    // STUDENT ANSWER END
};

#endif