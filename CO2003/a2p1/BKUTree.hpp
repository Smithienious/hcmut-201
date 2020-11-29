/************
 * @file BKUTree.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main implementation for Assignment 2 Phase 1
 *
 * Learners are expected to be able to use BST, specifically AVL and Splay Tree
 * AVL tree stores the BST structure, Splay tree stores recently accessed elements
 *
 * @version 0.1.4
 * @date 2020-11-30
 *
 * @copyright Copyright (c) 2020
 ************/

#ifndef BKU_TREE_HPP
#define BKU_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>

#include <functional>

#define MAX(A, B) (A > B ? A : B)

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
    queue<K> keys; // recently accessed data
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5) : maxNumOfKeys(maxNumOfKeys) {}
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
        private:
            Entry *entry;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;
            friend class SplayTree;

        public:
            Node(Entry *entry = nullptr, Node *left = nullptr, Node *right = nullptr)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = nullptr;
            }
            void setCorr(typename AVLTree::Node *iCorr)
            {
                corr = iCorr;
                return;
            }
        };

    public:
        Node *root;

        SplayTree() : root(nullptr){};
        ~SplayTree() { this->clear(); };

        void add(K, V);
        Node *add(Entry *);
        void remove(K);
        V search(K);

        void traverseNLR(void (*)(K, V));

        void clear();

        void setCorr(Node *, typename AVLTree::Node *);
        void splay(Node *);
        int getHeight(Node *);
        int getBalance(Node *);
        Node *rotateLeft(Node *);
        Node *rotateRight(Node *);
    }; // class SplayTree

    /************
     * @brief Store the BST structure
     ************/
    class AVLTree
    {
    public:
        class Node
        {
        private:
            Entry *entry;
            Node *left;
            Node *right;
            int balance; // height(left subtree) - height(right subtree)
            typename SplayTree::Node *corr;
            friend class AVLTree;

        public:
            Node(Entry *entry = nullptr, Node *left = nullptr, Node *right = nullptr)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = nullptr;
            }
            void setCorr(typename SplayTree::Node *iCorr)
            {
                corr = iCorr;
                return;
            }
        };

    public:
        Node *root;

        AVLTree() : root(nullptr){};
        ~AVLTree() { this->clear(); };

        void add(K, V);
        Node *add(Entry *);
        void remove(K);
        V search(K);

        void traverseNLR(void (*)(K, V));

        void clear();

        void setCorr(Node *, typename SplayTree::Node *);
        int getHeight(Node *);
        int getBalance(Node *);
        Node *rotateLeft(Node *);
        Node *rotateRight(Node *);
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
    if (keys.size() >= maxNumOfKeys)
        keys.pop();

    Entry *newEntry = new Entry(key, value);
    keys.push(key);

    if (avl == nullptr)
        avl = new AVLTree();
    if (splay == nullptr)
        splay = new SplayTree();

    typename AVLTree::Node *avlNode = avl->add(newEntry);
    typename SplayTree::Node *splayNode = splay->add(newEntry);
    avl->setCorr(avlNode, splayNode);
    splay->setCorr(splayNode, avlNode);

    return;
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
    // *
    typename AVLTree::Node *splay2avl = splay->corr;
    typename SplayTree::Node *avl2splay = avl->corr;

    // * If key is at root -> return root, else continue
    if (splay->entry->key == key)
        return splay->entry->value;

    // * If key is in queue -> find in Splay, else continue
    queue<K> tmpKeys = keys;
    while (tmpKeys.size > 0)
    {
        if (tmpKeys.front() != key)
            tmpKeys.pop();
        else
            return splay->search(key);
    }

    // * Try searching on AVL from Splay root in AVL. If found -> return key, else continue
    try
    {
        return splay2avl->search(key);
    }
    catch (...)
    {
        // * Do nothing
    }

    // * Try searching on AVL from root. If node equals corresponding AVL node or not found -> throw not found, else continue
    try
    {
        function<typename SplayTree::Node *(K, typename AVLTree::Node *, typename AVLTree::Node *)> recursiveSearch = [&](K key, typename AVLTree::Node *pR, typename AVLTree::Node *exitNode) {
            if (pR != nullptr && pR != exitNode)
            {
                if (key == pR->entry->key)
                    return pR->corr;
                if (key < pR->entry->key)
                    recursiveSearch(key, pR->left);
                if (key > pR->entry->value)
                    recursiveSearch(key, pR->right);
            }
            else
            {
                throw "Not found";
            }
        };

        avl2splay = recursiveSearch(key, avl, splay2avl);
    }
    catch (...)
    {
        // * Do nothing
    }

    // TODO

    return avl2splay->entry->value;
}

/************
 * @brief Pre-order traversal on the AVL tree
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::traverseNLROnAVL(void (*func)(K, V))
{
    avl->traverseNLR(func);
    return;
}

/************
 * @brief Pre-order traversal on the Splay tree
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::traverseNLROnSplay(void (*func)(K, V))
{
    splay->traverseNLR(func);
    return;
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
    avl->clear();
    splay->clear();
    return;
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
    Entry *newEntry = new Entry(key, value);
    add(newEntry);
    return;
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
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::add(Entry *entry)
{
    Node *newNode = new Node(entry);

    function<Node *(Node *, Node *)> recursiveAdd = [&](Node *pI, Node *pR) {
        // * Return node for insertion
        if (pR == nullptr)
            return pI;

        if (pI->entry->key == pR->entry->key)
            throw "Duplicate key";

        if (pI->entry->key < pR->entry->key)
            pR->left = recursiveAdd(pI, pR->left);
        if (pI->entry->key > pR->entry->key)
            pR->right = recursiveAdd(pI, pR->right);

        // TODO

        // * Get balance for rotation
        int subBal = getBalance(pR);

        // * Left rotate
        if (subBal > 1 && pI->entry->key < pR->entry->key)
        {
            return rotateRight(pR);
        }

        // * Right rotate
        if (subBal < -1 && pI->entry->key > pR->entry->key)
        {
            return rotateLeft(pR);
        }

        // * Left Right rotate
        if (subBal > 1 && pI->entry->key > pR->entry->key)
        {
            pR->left = rotateLeft(pR->left);
            return rotateRight(pR);
        }

        // * Right Left rotate
        if (subBal < -1 && pI->entry->key < pR->entry->key)
        {
            pR->right = rotateRight(pR->right);
            return rotateLeft(pR);
        }

        return pR;
    };

    root = recursiveAdd(newNode, root);
    return newNode;
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
    function<V(K, Node *)> recursiveSearch = [&](K key, Node *pR) {
        if (pR != nullptr)
        {
            if (key == pR->entry->key)
                return pR->entry->value;
            if (key < pR->entry->key)
                recursiveSearch(key, pR->left);
            if (key > pR->entry->value)
                recursiveSearch(key, pR->right);
        }
        else
        {
            throw "Not found";
        }
    };

    return recursiveSearch(key, root);
}

/************
 * @brief Pre-order traversal
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::traverseNLR(void (*func)(K, V))
{
    function<void(void (*)(K, V), Node *)> recursiveNLR = [&](void (*func)(K, V), Node *pR) {
        if (pR == nullptr)
            return;

        (*func)(pR->entry->key, pR->entry->value);

        if (pR->left != nullptr)
            recursiveNLR(func, pR->left);
        if (pR->right != nullptr)
            recursiveNLR(func, pR->right);
    };

    recursiveNLR(func, root);
}

/************
 * @brief Free everything, not including entry
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::clear()
{
    function<void(Node *)> recursiveClear = [&](Node *pR) {
        if (pR != nullptr)
        {
            clear(pR->left);
            clear(pR->right);
            delete pR;
        }
    };

    recursiveClear(root);
}

/************
 * @brief Set corresponding AVL node
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @param iCorr
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::setCorr(Node *pR, typename BKUTree<K, V>::AVLTree::Node *iCorr)
{
    pR->setCorr(iCorr);
    return;
}

/************
 * @brief Splaying
 *
 * @tparam K
 * @tparam V
 * @param pR
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::splay(Node *pR)
{
    // TODO
}

/************
 * @brief Get height of a node counting from leaf
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return int
 ************/
template <class K, class V>
int BKUTree<K, V>::SplayTree::getHeight(Node *pR)
{
    if (pR == nullptr)
        return 0;
    return 1 + MAX(getHeight(pR->left), getHeight(pR->right));
}

/************
 * @brief Get balance of a node (left height - right height)
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return int
 ************/
template <class K, class V>
int BKUTree<K, V>::SplayTree::getBalance(Node *pR)
{
    if (pR == nullptr)
        return 0;
    return getHeight(pR->left) - getHeight(pR->right);
}

/************
 * @brief Rotate left with pR as pivot
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return BKUTree<K, V>::SplayTree::Node*
 ************/
template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rotateLeft(Node *pR)
{
    Node *tmpRight = pR->right;
    Node *tmpRLeft = tmpRight->left;

    tmpRight->left = pR;
    pR->right = tmpRLeft;

    return tmpRight;
}

/************
 * @brief Rotate right with pR as pivot
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return BKUTree<K, V>::SplayTree::Node*
 ************/
template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rotateRight(Node *pR)
{
    Node *tmpLeft = pR->left;
    Node *tmpLRight = tmpLeft->right;

    tmpLeft->right = pR;
    pR->left = tmpLRight;

    return tmpLeft;
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
    Entry *newEntry = new Entry(key, value);
    add(newEntry);
    return;
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
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::add(Entry *entry)
{
    Node *newNode = new Node(entry);

    function<Node *(Node *, Node *)> recursiveAdd = [&](Node *pI, Node *pR) {
        // * Return node for insertion
        if (pR == nullptr)
            return pI;

        if (pI->entry->key == pR->entry->key)
            throw "Duplicate key";

        if (pI->entry->key < pR->entry->key)
            pR->left = recursiveAdd(pI, pR->left);
        if (pI->entry->key > pR->entry->key)
            pR->right = recursiveAdd(pI, pR->right);

        // * Get balance for rotation
        int subBal = getBalance(pR);

        // * Left rotate
        if (subBal > 1 && pI->entry->key < pR->entry->key)
        {
            return rotateRight(pR);
        }

        // * Right rotate
        if (subBal < -1 && pI->entry->key > pR->entry->key)
        {
            return rotateLeft(pR);
        }

        // * Left Right rotate
        if (subBal > 1 && pI->entry->key > pR->entry->key)
        {
            pR->left = rotateLeft(pR->left);
            return rotateRight(pR);
        }

        // * Right Left rotate
        if (subBal < -1 && pI->entry->key < pR->entry->key)
        {
            pR->right = rotateRight(pR->right);
            return rotateLeft(pR);
        }

        return pR;
    };

    root = recursiveAdd(newNode, root);
    return newNode;
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
    function<V(K, Node *)> recursiveSearch = [&](K key, Node *pR) {
        if (pR != nullptr)
        {
            if (key == pR->entry->key)
                return pR->entry->value;
            if (key < pR->entry->key)
                recursiveSearch(key, pR->left);
            if (key > pR->entry->value)
                recursiveSearch(key, pR->right);
        }
        else
        {
            throw "Not found";
        }
    };

    return recursiveSearch(key, root);
}

/************
 * @brief Pre-order traversal
 *
 * @tparam K
 * @tparam V
 * @param func
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::traverseNLR(void (*func)(K, V))
{
    function<void(void (*)(K, V), Node *)> recursiveNLR = [&](void (*func)(K, V), Node *pR) {
        if (pR == nullptr)
            return;

        (*func)(pR->entry->key, pR->entry->value);

        if (pR->left != nullptr)
            recursiveNLR(func, pR->left);
        if (pR->right != nullptr)
            recursiveNLR(func, pR->right);
    };

    recursiveNLR(func, root);
}

/************
 * @brief Free everything, including entry
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::clear()
{
    function<void(Node *)> recursiveClear = [&](Node *pR) {
        if (pR != nullptr)
        {
            clear(pR->left);
            clear(pR->right);
            delete pR->entry;
            delete pR;
        }
    };

    recursiveClear(root);
}

/************
 * @brief Set corresponding Splay node
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @param iCorr
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::setCorr(Node *pR, typename BKUTree<K, V>::SplayTree::Node *iCorr)
{
    pR->setCorr(iCorr);
    return;
}

/************
 * @brief Get height of a node counting from leaf
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return int
 ************/
template <class K, class V>
int BKUTree<K, V>::AVLTree::getHeight(Node *pR)
{
    if (pR == nullptr)
        return 0;
    return 1 + MAX(getHeight(pR->left), getHeight(pR->right));
}

/************
 * @brief Get balance of a node (left height - right height)
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return int
 ************/
template <class K, class V>
int BKUTree<K, V>::AVLTree::getBalance(Node *pR)
{
    if (pR == nullptr)
        return 0;
    return getHeight(pR->left) - getHeight(pR->right);
}

/************
 * @brief Rotate left with pR as pivot
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return BKUTree<K, V>::AVLTree::Node*
 ************/
template <class K, class V>
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::rotateLeft(Node *pR)
{
    Node *tmpRight = pR->right;
    Node *tmpRLeft = tmpRight->left;

    tmpRight->left = pR;
    pR->right = tmpRLeft;

    return tmpRight;
}

/************
 * @brief Rotate right with pR as pivot
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return BKUTree<K, V>::AVLTree::Node*
 ************/
template <class K, class V>
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::rotateRight(Node *pR)
{
    Node *tmpLeft = pR->left;
    Node *tmpLRight = tmpLeft->right;

    tmpLeft->right = pR;
    pR->left = tmpLRight;

    return tmpLeft;
}

#endif
