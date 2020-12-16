/************
 * @file BKUTree.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main implementation for Assignment 2 Phase 1
 *
 * Learners are expected to be able to use BST, specifically AVL and Splay Tree
 * AVL tree stores the BST structure, Splay tree stores recently accessed elements
 *
 * @version 0.3.0
 * @date 2020-12-16
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

template <class K, class V>
class BKUTree
{
public:
  class AVLTree;
  class SplayTree;

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
    void tree(string, Node *, bool);
    Node *rotateLeft(Node *);
    Node *rotateRight(Node *);
  }; // class SplayTree

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
};   // class BKUTree

template <class K, class V>
void BKUTree<K, V>::add(K key, V value)
{
  if (int(keys.size()) >= maxNumOfKeys)
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

template <class K, class V>
void BKUTree<K, V>::remove(K key)
{
  avl->remove(key);
  splay->remove(key);
  return;
}

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

template <class K, class V>
void BKUTree<K, V>::traverseNLROnAVL(void (*func)(K, V))
{
  avl->traverseNLR(func);
  return;
}

template <class K, class V>
void BKUTree<K, V>::traverseNLROnSplay(void (*func)(K, V))
{
  splay->traverseNLR(func);
  return;
}

template <class K, class V>
void BKUTree<K, V>::clear()
{
  avl->clear();
  splay->clear();
  while (!keys.empty())
    keys.pop();
  return;
}

template <class K, class V>
void BKUTree<K, V>::printAVL()
{
  avl->tree("", avl->root, false);
  return;
}

template <class K, class V>
void BKUTree<K, V>::printSplay()
{
  splay->tree("", splay->root, false);
  return;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::add(K key, V value)
{
  Entry *newEntry = new Entry(key, value);
  add(newEntry);
  return;
}

template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::add(Entry *entry)
{
  Node *newNode = new Node(entry);

  function<Node *(Node *, Node *, int &)> recursiveAdd = [&](Node *pI, Node *pR, int &relativeHeight) {
    if (pR == nullptr)
    {
      relativeHeight = 1;
      return pI;
    }

    if (pI->entry->key == pR->entry->key)
      throw "Duplicate key";
    if (pI->entry->key < pR->entry->key)
      pR->left = recursiveAdd(pI, pR->left, relativeHeight);
    if (pI->entry->key > pR->entry->key)
      pR->right = recursiveAdd(pI, pR->right, relativeHeight);

    if (pR == root && relativeHeight == 1)
    {
      // * Zig
      if (pI->entry->key < pR->entry->key)
        return rotateRight(pR);
      // * Zag
      if (pI->entry->key > pR->entry->key)
        return rotateLeft(pR);
    }
    else if (relativeHeight == 2)
    {
      relativeHeight = 1;

      if (pI->entry->key < pR->entry->key)
      {
        // * Zig Zig
        if (pI->entry->key < pR->left->entry->key)
        {
          Node *tmp = rotateRight(pR);
          return rotateRight(tmp);
        }
        // * Zig Zag
        if (pI->entry->key > pR->left->entry->key)
        {
          pR->left = rotateLeft(pR->left);
          return rotateRight(pR);
        }
      }
      if (pI->entry->key > pR->entry->key)
      {
        // * Zag Zag
        if (pI->entry->key > pR->right->entry->key)
        {
          Node *tmp = rotateLeft(pR);
          return rotateLeft(tmp);
        }
        // * Zag Zig
        if (pI->entry->key < pR->right->entry->key)
        {
          pR->right = rotateRight(pR->right);
          return rotateLeft(pR);
        }
      }
    }
    else if (relativeHeight == 1)
    {
      relativeHeight += 1;
      return pR;
    }

    return pR;
  };

  int i = 0;
  root = recursiveAdd(newNode, root, i);
  return newNode;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::remove(K key)
{
  // TODO
}

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
  root = splay(pI->entry->key, root);
  return pI;
}

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

template <class K, class V>
void BKUTree<K, V>::SplayTree::setCorr(Node *pR, typename BKUTree<K, V>::AVLTree::Node *iCorr)
{
  pR->setCorr(iCorr);
  return;
}

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

template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rotateLeft(Node *pR)
{
  Node *tmp = pR->right;
  pR->right = tmp->left;
  tmp->left = pR;
  return tmp;
}

template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rotateRight(Node *pR)
{
  Node *tmp = pR->left;
  pR->left = tmp->right;
  tmp->right = pR;
  return tmp;
}

template <class K, class V>
void BKUTree<K, V>::AVLTree::add(K key, V value)
{
  Entry *newEntry = new Entry(key, value);
  add(newEntry);
  return;
}

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

template <class K, class V>
void BKUTree<K, V>::AVLTree::remove(K key) // ! 3
{
  function<Node *(K, Node *, Node *)>
      recursiveDelete = [&](K key, Node *pR, Node *pN) {
        if (pR == nullptr)
          throw "Not found";

        Node *tmp = nullptr;
        bool isRight = false;

        if (key < pR->entry->key)
          pR->left = recursiveDelete(key, pR->left, pR);
        else if (key > pR->entry->key)
          pR->right = recursiveDelete(key, pR->right, pR);
        else
        {
          // * No or one child
          if (pR->left == nullptr || pR->right == nullptr)
          {
            tmp = (pR->left) ? pR->left : pR->right;

            if (pN != nullptr)
            {
              if (pN->left == pR)
              {
                pN->left = tmp;
                isRight = false;
              }
              else
              {
                pN->right = tmp;
                isRight = true;
              }
            }

            delete pR->entry;
            delete pR;
            pR = nullptr;
            if (tmp != nullptr)
              tmp->left = tmp->right = nullptr;

            if (pN == nullptr)
              return pN;
          }
          else // * Two children
          {
            // http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=130606#p427519
            Node *curr = pR->left, *par = pR->left;
            while (curr->right != nullptr)
            {
              par = curr;
              curr = curr->right;
            }

            if (pN != nullptr)
            {
              if (pN->left == pR)
              {
                pN->left = tmp;
                isRight = false;
              }
              else
              {
                pN->right = tmp;
                isRight = true;
              }
            }
            else
              root = curr;

            if (curr == par)
            {
              pR->left = curr->left;
              curr->left = pR;
              curr->right = pR->right;
              pR->right = nullptr;
            }
            else
            {
              curr->left = pR->left;
              curr->right = pR->right;
              par->right = pR;
              pR->left = pR->right = nullptr;
            }

            tmp = curr;
            tmp->left = recursiveDelete(pR->entry->key, tmp->left, tmp);
          }
        }

        if (pN != nullptr)
        {
          if (isRight)
            pR = pN->right;
          else
            pR = pN->left;
        }

        if (pR == nullptr || pR->entry == nullptr)
          return tmp;

        // *
        pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;

        // *
        pR->balance = findBalance(pR);

        if ((pR->balance > 1) &&
            (key < pR->entry->key || pR->right == nullptr))
        {
          return rotateRight(pR);
        }

        if ((pR->balance < -1) &&
            (key > pR->entry->key || pR->left == nullptr))
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

  root = recursiveDelete(key, root, nullptr);
  return;
}

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

template <class K, class V>
void BKUTree<K, V>::AVLTree::setCorr(Node *pR, typename BKUTree<K, V>::SplayTree::Node *iCorr)
{
  pR->setCorr(iCorr);
  return;
}

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

template <class K, class V>
int BKUTree<K, V>::AVLTree::findHeight(Node *pR)
{
  if (pR == nullptr)
    return 0;
  return pR->height;
}

template <class K, class V>
int BKUTree<K, V>::AVLTree::findBalance(Node *pR)
{
  if (pR == nullptr)
    return 0;
  return findHeight(pR->left) - findHeight(pR->right);
}

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
