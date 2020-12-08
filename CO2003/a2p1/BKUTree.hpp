/************
 * @file BKUTree.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main implementation for Assignment 2 Phase 1
 *
 * Learners are expected to be able to use BST, specifically AVL and Splay Tree
 * AVL tree stores the BST structure, Splay tree stores recently accessed elements
 *
 * @version 0.2.0
 * @date 2020-12-08
 *
 * @copyright Copyright (c) 2020
 ************/

#ifndef BKU_TREE_HPP
#define BKU_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>

#include <functional>

#define MAX(A, B) ((A > B) ? A : B)

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

    void printAVL();
    void printSplay();

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
            Node *north;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;
            friend class SplayTree;

        public:
            Node(Entry *entry = nullptr, Node *north = nullptr, Node *left = nullptr, Node *right = nullptr) : north(north)
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
        void tree(string, Node *, bool);
        Node *splay(Node *, Node *);
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
            int height;
            Node *left;
            Node *right;
            int balance;
            typename SplayTree::Node *corr;
            friend class AVLTree;

        public:
            Node(Entry *entry = nullptr, Node *left = nullptr, Node *right = nullptr) : height(1)
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
        void tree(string, Node *, bool);
        int findHeight(Node *);
        int findBalance(Node *);
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
    keys.push(key);

    Entry *newEntry = new Entry(key, value);

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
    avl->remove(key);
    splay->remove(key);
    return;
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
    // * 1. If key is at root -> return root, else continue
    if (splay->entry->key == key)
        return splay->entry->value;

    // * 2. If key is in queue -> find in Splay, else continue
    queue<K> tmpKeys = keys;
    while (tmpKeys.size > 0)
    {
        if (tmpKeys.front() != key)
            tmpKeys.pop();
        else
            return splay->search(key);
    }

    // * 3a. Get Splay root in AVL
    typename AVLTree::Node *splay2avl = splay->corr;
    typename SplayTree::Node *avl2splay = avl->corr;

    // * 3b. Try searching on AVL from Splay root in AVL. If found -> return key, else continue
    try
    {
        // * 3c.
        return splay2avl->search(key);
    }
    catch (...)
    {
        // * Do nothing
    }

    // * 3d. Try searching on AVL from root. If node equals corresponding AVL node or not found -> throw not found, else continue
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

    // * 3e.
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
    while (!keys.empty())
        keys.pop();
    return;
}

/************
 * @brief Visualize AVL tree
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::printAVL()
{
    avl->tree("", avl->root, false);
    return;
}

/************
 * @brief Visualize Splay tree
 *
 * @tparam K
 * @tparam V
 ************/
template <class K, class V>
void BKUTree<K, V>::printSplay()
{
    splay->tree("", splay->root, false);
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
 * @brief Add an entry to root of Splay tree
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

        // * Bring closest leaf to root
        pR = splay(pI, pR);

        if (pI->entry->key == pR->entry->key)
            throw "Duplicate key";

        if (pI->entry->key < pR->entry->key)
        {
            pI->right = pR;
            pI->left = pR->left;
            pR->left = nullptr;
        }
        if (pI->entry->key > pR->entry->key)
        {
            pI->left = pR;
            pI->right = pR->right;
            pR->right = nullptr;
        }

        return pI;
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
V BKUTree<K, V>::SplayTree::search(K key) // TODO
{
    function<Node *(K, Node *)> recursiveSearch = [&](K key, Node *pR) {
        if (pR != nullptr)
        {
            if (key == pR->entry->key)
                return pR;
            if (key < pR->entry->key)
                return recursiveSearch(key, pR->left);
            if (key > pR->entry->value)
                return recursiveSearch(key, pR->right);
        }
        else
        {
            throw "Not found";
        }
    };

    Node *pI = recursiveSearch(key, root);
    root = splay(pI, root);
    return pI;
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
 * @brief Print AVL tree
 *
 * @tparam K
 * @tparam V
 * @param prefix
 * @param pR
 * @param hasRight
 ************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::tree(string prefix, Node *pR, bool hasRight)
{
    cout << prefix;

    // ┘ ┐ ┌ └ ┼ ─ ├ ┤ ┴ ┬ │
    cout << ((hasRight) ? "├──" : "└──");

    // * Print the value of the node
    if (pR)
    {
        cout << pR->entry->key;
        // cout << " [" << pR->entry->value << "]";
        cout << endl;
    }
    else
    {
        cout << "Ø" << endl;
        return;
    }

    // * Enter the next tree level - left and right branch
    if (pR->left != nullptr || pR->right != nullptr)
    {
        tree(prefix + ((hasRight) ? "│   " : "    "), pR->right, true);
        tree(prefix + ((hasRight) ? "│   " : "    "), pR->left, false);
    }

    return;
}

/************
 * @brief Splaying
 *
 * @tparam K
 * @tparam V
 * @param pI
 * @param pR
 ************/
template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::splay(Node *pI, Node *pR) // TODO
{
    // * Base case
    if (pR == nullptr || pI->entry->key == pR->entry->key)
        return pR;

    // *
    if (pI->entry->key < pR->entry->key)
    {
        if (pR->left == nullptr || pI->entry->key == pR->left->entry->key)
            return pR;

        // *
        if (pI->entry->key < pR->left->entry->key)
        {
            pR->left->left = splay(pI, pR->left->left);
            if (pI->entry->key == pR->left->left->entry->key)
                pR->left = rotateRight(pR->left);
            pR = rotateRight(pR);
        }
        // *
        else if (pI->entry->key > pR->left->entry->key)
        {
            // *
            pR->left->right = splay(pI, pR->left->right);
            if (pR->left->right != nullptr)
                pR->left = rotateLeft(pR->left);
        }

        return (pR->left == nullptr) ? pR : rotateRight(pR);
    }
    else
        // *
        if (pI->entry->key > pR->entry->key)
    {
        if (pR->right == nullptr)
            return pR;

        // *
        if (pI->entry->key < pR->right->entry->key)
        {
            // * Make pI root of right-left
            pR->right->left = splay(pI, pR->right->left);
            if (pR->right->left != nullptr)
                pR->right = rotateRight(pR->right);
        }
        else
            // *
            if (pI->entry->key > pR->right->entry->key)
        {
            // *
            pR->right->right = splay(pI, pR->right->right);
            pR = rotateLeft(pR);
        }

        return (pR->right == nullptr) ? pR : rotateLeft(pR);
    }

    return pR;
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
    Node *tmp = pR->right;
    pR->right = tmp->left;
    tmp->left = pR;
    return tmp;
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
    Node *tmp = pR->left;
    pR->left = tmp->right;
    tmp->right = pR;
    return tmp;
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
 * @brief Add an entry to leaf of AVL tree
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
        // *
        if (pR == nullptr)
            return pI;

        // *
        if (pI->entry->key == pR->entry->key)
            throw "Duplicate key";

        if (pI->entry->key < pR->entry->key)
            pR->left = recursiveAdd(pI, pR->left);
        if (pI->entry->key > pR->entry->key)
            pR->right = recursiveAdd(pI, pR->right);

        // *
        pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;

        // *
        pR->balance = findBalance(pR);

        if (pR->balance > 1 && pI->entry->key < pR->entry->key)
        {
            return rotateRight(pR);
        }

        if (pR->balance < -1 && pI->entry->key > pR->entry->key)
        {
            return rotateLeft(pR);
        }

        if (pR->balance > 1 && pI->entry->key > pR->entry->key)
        {
            pR->left = rotateLeft(pR->left);
            return rotateRight(pR);
        }

        if (pR->balance < -1 && pI->entry->key < pR->entry->key)
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
void BKUTree<K, V>::AVLTree::remove(K key) // TODO
{
    function<Node *(Node *)> minOfRight = [](Node *pR) {
        Node *curr = pR->right;
        while (curr->left != nullptr)
            curr = curr->left;
        return curr;
    };

    function<Node *(K, Node *)> recursiveDelete = [&](K key, Node *pR) {
        if (pR == nullptr)
            throw "Not found";

        if (key < pR->entry->key)
            pR->left = recursiveDelete(key, pR->left);
        else if (key > pR->entry->key)
            pR->right = recursiveDelete(key, pR->right);
        else
        {
            // * Node with no or one child
            if (pR->left == nullptr || pR->right == nullptr)
            {
                Node *tmp = (pR->left) ? pR->left : pR->right;

                if (tmp == nullptr) // * No child
                {
                    tmp = pR;
                    pR = nullptr;
                }
                else // * One child
                    *pR = *tmp;

                delete tmp->entry;
                delete tmp;
            }
            else // * Two children
            {
                Node *tmp = minOfRight(pR);
                pR->entry = tmp->entry;
                pR->right = recursiveDelete(tmp->entry->key, pR->right);
            }
        }

        if (pR == nullptr)
            return pR;

        // *
        pR->balance = findBalance(pR);

        if (pR->balance > 1 && key < pR->entry->key)
        {
            return rotateRight(pR);
        }

        if (pR->balance < -1 && key > pR->entry->key)
        {
            return rotateLeft(pR);
        }

        if (pR->balance > 1 && key > pR->entry->key)
        {
            pR->left = rotateLeft(pR->left);
            return rotateRight(pR);
        }

        if (pR->balance < -1 && key < pR->entry->key)
        {
            pR->right = rotateRight(pR->right);
            return rotateLeft(pR);
        }

        return pR;
    };

    root = recursiveDelete(key, root);
    return;
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
    return;
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
    return;
}

/************
 * @brief Print AVL tree
 *
 * @tparam K
 * @tparam V
 * @param prefix
 * @param pR
 * @param hasRight
 ************/
template <class K, class V>
void BKUTree<K, V>::AVLTree::tree(string prefix, Node *pR, bool hasRight)
{
    cout << prefix;

    // ┘ ┐ ┌ └ ┼ ─ ├ ┤ ┴ ┬ │
    cout << ((hasRight) ? "├──" : "└──");

    // * Print the value of the node
    if (pR)
    {
        cout << pR->entry->key;
        // cout << " [" << pR->height << "]";
        // cout << " {" << pR->balance << "}";
        cout << endl;
    }
    else
    {
        cout << "Ø" << endl;
        return;
    }

    // * Enter the next tree level - left and right branch
    if (pR->left != nullptr || pR->right != nullptr)
    {
        tree(prefix + ((hasRight) ? "│   " : "    "), pR->right, true);
        tree(prefix + ((hasRight) ? "│   " : "    "), pR->left, false);
    }

    return;
}

/************
 * @brief Get height of a node
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return int
 ************/
template <class K, class V>
int BKUTree<K, V>::AVLTree::findHeight(Node *pR)
{
    if (pR == nullptr)
        return 0;
    return pR->height;
}

/************
 * @brief Calculate balace of a node
 *
 * @tparam K
 * @tparam V
 * @param pR
 * @return int
 ************/
template <class K, class V>
int BKUTree<K, V>::AVLTree::findBalance(Node *pR)
{
    if (pR == nullptr)
        return 0;
    return findHeight(pR->left) - findHeight(pR->right);
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
    Node *tmp = pR->right;

    pR->right = tmp->left;
    tmp->left = pR;

    pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;
    tmp->height = MAX(findHeight(tmp->left), findHeight(tmp->right)) + 1;

    pR->balance = findBalance(pR);
    tmp->balance = findBalance(tmp);

    return tmp;
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
    Node *tmp = pR->left;

    pR->left = tmp->right;
    tmp->right = pR;

    pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;
    tmp->height = MAX(findHeight(tmp->left), findHeight(tmp->right)) + 1;

    pR->balance = findBalance(pR);
    tmp->balance = findBalance(tmp);

    return tmp;
}

#endif
