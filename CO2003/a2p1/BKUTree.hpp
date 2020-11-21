/************
 * @file BKUTree.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main implementation for Assignment 2 Phase 1
 *
 * Learners are expected to be able to use BST, specifically AVL and Splay Tree
 * AVL tree stores the BST structure, Splay tree stores recently accessed elements
 *
 * @version 0.1.1
 * @date 2020-11-22
 *
 * @copyright Copyright (c) 2020
 ************/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/************
 * @brief Main structure
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
class BKUTree
{
public:
    class AVLTree;
    class SplayTree;

    /************
     * @brief Memory allocator
     ************/
    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    }; // class Entry

private:
    AVLTree *avl;
    SplayTree *splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5) {}
    ~BKUTree() { this->clear(); }

    void add(K, V);
    void remove(K);
    V search(K, vector<K> &);

    void traverseNLROnAVL(void (*)(K, V));
    void traverseNLROnSplay(void (*)(K, V));

    void clear();

    /************
     * @brief Store recently accessed data with order
     ************/
    class SplayTree
    {
    public:
        class Node
        {
            Entry *entry;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;

            Node(Entry *entry = nullptr, Node *left = nullptr, Node *right = nullptr)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = nullptr;
            }
        };

    public:
        Node *root;

        SplayTree() : root(nullptr){};
        ~SplayTree() { this->clear(); };

        void add(K, V);
        void add(Entry *);
        void remove(K);
        V search(K);

        void traverseNLR(void (*)(K, V));

        void clear();
    }; // class SplayTree

    /************
     * @brief Store the BST structure
     ************/
    class AVLTree
    {
    public:
        class Node
        {
            Entry *entry;
            Node *left;
            Node *right;
            int balance;
            typename SplayTree::Node *corr;

            Node(Entry *entry = nullptr, Node *left = nullptr, Node *right = nullptr)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = nullptr;
            }
        };

    public:
        Node *root;

        AVLTree() : root(nullptr){};
        ~AVLTree() { this->clear(); };

        void add(K, V);
        void add(Entry *);
        void remove(K);
        V search(K);

        void traverseNLR(void (*)(K, V));

        void clear();
    }; // class AVLTree
};     // class BKUTree

/************
 * @brief Add an element with key and value to BKUTree
 *        Throw "Duplicate key" if key exists
 *
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 ************/
template <class K, class V>
void BKUTree<K, V>::add(K key, V value)
{
    // TODO
}

/************
 * @brief Remove an element with key from BKUTree
 *        Throw "Not found" if key does not exist
 *
 * @tparam K
 * @tparam V
 * @param key
 ************/
template <class K, class V>
void BKUTree<K, V>::remove(K key)
{
    // TODO
}

/************
 * @brief Find an element with key in BKUTree
 *        Throw "Not found" if key does not exist
 *
 * @tparam K
 * @tparam V
 * @param key
 * @param traversedList store traversed nodes with order
 * @return V
 ************/
template <class K, class V>
V BKUTree<K, V>::search(K key, vector<K> &traversedList)
{
    // TODO
}

/************
 * @brief Pre-order traversal on the AVL tree
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::traverseNLROnAVL(void (*func)(K key, V value))
{
    // TODO
}

/************
 * @brief Pre-order traversal on the Splay tree
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::traverseNLROnSplay(void (*func)(K key, V value))
{
    // TODO
}

/************
 * @brief Free everything
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::clear()
{
    // TODO
}

/************
 * @brief Add an element with key and value to BKUTree
 *        Throw "Duplicate key" if key exists
 *
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::add(K key, V value)
{
    // TODO
}

/************
 * @brief Add an entry to BKUTree
 *        Throw "Duplicate key" if entry exists
 *
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::add(Entry *entry)
{
    // TODO
}

/************
 * @brief Remove an element with key from BKUTree
 *        Throw "Not found" if key does not exist
 *
 * @tparam K
 * @tparam V
 * @param key
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::remove(K key)
{
    // TODO
}

/************
 * @brief Find an element with key in BKUTree
 *        Throw "Not found" if key does not exist
 *
 * @tparam K
 * @tparam V
 * @param key
 * @return V
 ************/
template <class K, class V>
V BKUTree<K, V>::SplayTree::search(K key)
{
    // TODO
}

/************
 * @brief Pre-order traversal
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::traverseNLR(void (*func)(K key, V value))
{
    // TODO
}

/************
 * @brief Free everything
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::clear()
{
    // TODO
}

/************
 * @brief Add an element with key and value to BKUTree
 *        Throw "Duplicate key" if key exists
 *
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::add(K key, V value)
{
    // TODO
}

/************
 * @brief Add an entry to BKUTree
 *        Throw "Duplicate key" if entry exists
 *
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::add(Entry *entry)
{
    // TODO
}

/************
 * @brief Remove an element with key from BKUTree
 *        Throw "Not found" if key does not exist
 *
 * @tparam K
 * @tparam V
 * @param key
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::remove(K key)
{
    // TODO
}

/************
 * @brief Find an element with key in BKUTree
 *        Throw "Not found" if key does not exist
 *
 * @tparam K
 * @tparam V
 * @param key
 * @return V
 ************/
template <class K, class V>
V BKUTree<K, V>::AVLTree::search(K key)
{
    // TODO
}

/************
 * @brief Pre-order traversal
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::traverseNLR(void (*func)(K key, V value))
{
    // TODO
}

/************
 * @brief Free everything
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::clear()
{
    // TODO
}
