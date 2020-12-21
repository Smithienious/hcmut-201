/************
 * @file BKUTree.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main implementation for Assignment 2 Phase 1
 *
 * Learners are expected to be able to use BST, specifically AVL and Splay Tree
 * AVL tree stores the BST structure, Splay tree stores recently accessed elements
 *
 * @version 0.4.3
 * @date 2020-12-21
 *
 * @copyright Copyright (c) 2020
 ************/

#ifndef BKU_TREE_HPP
#define BKU_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>

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
  queue<K> keys;
  int maxNumOfKeys;

public:
  BKUTree(int maxNumOfKeys = 5) : avl(nullptr), splay(nullptr), maxNumOfKeys(maxNumOfKeys) {}
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
      friend class BKUTree;

    public:
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
    Node *add(Entry *);
    void remove(K, bool deleteEntry = true);
    V search(K);

    void traverseNLR(void (*)(K, V));

    void clear(bool deleteEntry = true);

    Node *rAdd(Node *, Node *, int &);
    Node *rSearch(K, Node *, int &);
    Node *rartedSearch(K, Node *, int &, bool &, V &, vector<K> &);
    void rNLR(void (*)(K, V), Node *);
    void rClear(Node *, bool &);

    Node *rotateLeft(Node *);
    Node *rotateRight(Node *);
    void tree(string, Node *, bool);
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
      friend class BKUTree;

    public:
      Node(Entry *entry = nullptr, Node *left = nullptr, Node *right = nullptr) : height(1)
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
    Node *add(Entry *);
    void remove(K, bool deleteEntry = true);
    V search(K);

    void traverseNLR(void (*)(K, V));

    void clear(bool deleteEntry = true);

    Node *rAdd(Node *, Node *);
    Node *rRemove(K, Node *, Node *, bool &);
    Node *rSearch(K, Node *pR);
    Node *rartedSearch(K, Node *, Node *, V &, vector<K> &);
    void rNLR(void (*)(K, V), Node *);
    void rClear(Node *, bool &);

    int findHeight(Node *);
    int findBalance(Node *);
    Node *rotateLeft(Node *);
    Node *rotateRight(Node *);
    void tree(string, Node *, bool);
  }; // class AVLTree
};   // class BKUTree

template <class K, class V>
void BKUTree<K, V>::add(K key, V value)
{
  Entry *newEntry = new Entry(key, value);

  if (avl == nullptr)
    avl = new AVLTree();
  if (splay == nullptr)
    splay = new SplayTree();

  typename AVLTree::Node *avlNode = avl->add(newEntry);
  typename SplayTree::Node *splayNode = splay->add(newEntry);
  avlNode->corr = splayNode;
  splayNode->corr = avlNode;

  if (int(keys.size()) >= maxNumOfKeys)
    keys.pop();
  keys.push(key);

  return;
}

template <class K, class V>
void BKUTree<K, V>::remove(K key)
{
  queue<K> tmpKeys;
  while (!keys.empty())
  {
    if (key != tmpKeys.front())
      tmpKeys.push(keys.front());
    keys.pop();
  }
  keys = tmpKeys;

  avl->remove(key, false);
  splay->remove(key);

  if (int(keys.size()) >= maxNumOfKeys)
    keys.pop();
  if (splay->root != nullptr)
    keys.push(splay->root->entry->key);

  return;
}

template <class K, class V>
V BKUTree<K, V>::search(K key, vector<K> &traversedList)
{
  // * 1. If key is at root -> return root, else continue
  if (key == splay->root->entry->key)
    return splay->root->entry->value;

  // * 2. If key is in queue -> find in Splay, else continue
  queue<K> tmpKeys = keys;
  while (!tmpKeys.empty())
  {
    if (key != tmpKeys.front())
      tmpKeys.pop();
    else
    {
      if (tmpKeys.size() >= maxNumOfKeys)
        tmpKeys.pop();
      tmpKeys.push(key);
      int i = 0;
      bool splayed = false;
      V rValue;
      splay->root = splay->rartedSearch(key, splay->root, i, splayed, rValue, traversedList);
      return rValue;
    }
  }

  // * 3a. Get Splay root in AVL
  typename AVLTree::Node *splay2avl = splay->root->corr;

  // * 3b. Try searching on AVL from Splay root in AVL. If found -> return key, else continue
  typename AVLTree::Node *avlNode = nullptr;
  V rValue;
  try
  {
    // * 3c.
    avlNode = avl->rartedSearch(key, splay2avl, nullptr, rValue, traversedList);
  }
  catch (...)
  {
    // * 3d. Try searching on AVL from root. If node equals corresponding AVL node or not found -> throw not found, else continue
    avlNode = avl->rartedSearch(key, avl->root, splay2avl, rValue, traversedList);
  }

  // * 3e. With node found in AVL, splay Splay tree at AVL->corr
  typename SplayTree::Node *avl2splay = avlNode->corr;
  int i = 0;
  bool splayed = false;
  vector<K> tmpList;
  splay->root = splay->rartedSearch(key, splay->root, i, splayed, rValue, tmpList);

  // * 4.
  if (int(keys.size()) >= maxNumOfKeys)
    keys.pop();
  keys.push(key);
  return rValue;
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
  if (avl != nullptr)
  {
    avl->clear(false);
    delete avl;
    avl = nullptr;
  }

  if (splay != nullptr)
  {
    splay->clear();
    delete splay;
    splay = nullptr;
  }

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
  int i = 0;
  root = (root == nullptr) ? newNode : rAdd(newNode, root, i);
  return newNode;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::remove(K key, bool deleteEntry)
{
  int i = 0;
  root = rSearch(key, root, i);

  // * No or one child
  if (root->left == nullptr || root->right == nullptr)
  {
    Node *tmp = root;
    root = (root->left) ? root->left : root->right;
    if (deleteEntry == true)
      delete tmp->entry;
    delete tmp;
  }
  else // * Two children
  {
    i = 0;

    // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=130606#p427519
    Node *cur = root->left;
    while (cur->right != nullptr)
      cur = cur->right;

    K tmpKey = cur->entry->key;
    Node *exRoot = root;
    root = root->left;
    root = rSearch(tmpKey, root, i);
    root->right = exRoot->right;

    if (deleteEntry == true)
      delete exRoot->entry;
    else
      exRoot->entry = nullptr;

    delete exRoot;
  }

  return;
}

template <class K, class V>
V BKUTree<K, V>::SplayTree::search(K key)
{
  int i = 0;
  root = rSearch(key, root, i);
  return root->entry->value;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::traverseNLR(void (*func)(K, V))
{
  rNLR(func, root);
  return;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::clear(bool deleteEntry)
{
  if (root == nullptr)
    return;

  rClear(root, deleteEntry);
  root = nullptr;
  return;
}

template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rAdd(Node *pI, Node *pR, int &relativeHeight)
{
  if (pR == nullptr)
  {
    relativeHeight = 1;
    return pI;
  }
  if (pI->entry->key == pR->entry->key)
    throw "Duplicate key";
  if (pI->entry->key < pR->entry->key)
    pR->left = rAdd(pI, pR->left, relativeHeight);
  if (pI->entry->key > pR->entry->key)
    pR->right = rAdd(pI, pR->right, relativeHeight);

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
}

template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rSearch(K key, Node *pR, int &relativeHeight)
{
  if (pR == nullptr)
    throw "Not found";
  if (key == pR->entry->key)
  {
    relativeHeight = 1;
    return pR;
  }
  if (key < pR->entry->key)
    pR->left = rSearch(key, pR->left, relativeHeight);
  if (key > pR->entry->key)
    pR->right = rSearch(key, pR->right, relativeHeight);

  // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=130606#p427653
  if (pR == root && relativeHeight == 1)
  {
    // * Zig
    if (key < pR->entry->key)
      return rotateRight(pR);
    // * Zag
    if (key > pR->entry->key)
      return rotateLeft(pR);
  }
  else if (relativeHeight == 2)
  {
    relativeHeight = 1;

    if (key < pR->entry->key)
    {
      // * Zig Zig
      if (key < pR->left->entry->key)
      {
        Node *tmp = rotateRight(pR);
        return rotateRight(tmp);
      }
      // * Zig Zag
      if (key > pR->left->entry->key)
      {
        pR->left = rotateLeft(pR->left);
        return rotateRight(pR);
      }
    }
    if (key > pR->entry->key)
    {
      // * Zag Zag
      if (key > pR->right->entry->key)
      {
        Node *tmp = rotateLeft(pR);
        return rotateLeft(tmp);
      }
      // * Zag Zig
      if (key < pR->right->entry->key)
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
}

template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::rartedSearch(K key, Node *pR, int &relativeHeight, bool &splayed, V &rValue, vector<K> &traversedList)
{
  if (pR == nullptr)
    throw "Not found";
  if (key == pR->entry->key)
  {
    rValue = pR->entry->value;
    relativeHeight = 1;
    return pR;
  }

  traversedList.push_back(pR->entry->key);
  if (key < pR->entry->key)
    pR->left = rartedSearch(key, pR->left, relativeHeight, splayed, rValue, traversedList);
  if (key > pR->entry->value)
    pR->right = rartedSearch(key, pR->right, relativeHeight, splayed, rValue, traversedList);

  if (splayed == true)
    return pR;

  splayed = true;
  if (pR == root && relativeHeight == 1)
  {
    // * Zig
    if (key < pR->entry->key)
      return rotateRight(pR);
    // * Zag
    if (key > pR->entry->key)
      return rotateLeft(pR);
  }
  else if (relativeHeight == 2)
  {
    relativeHeight = 1;

    if (key < pR->entry->key)
    {
      // * Zig Zig
      if (key < pR->left->entry->key)
      {
        Node *tmp = rotateRight(pR);
        return rotateRight(tmp);
      }
      // * Zig Zag
      if (key > pR->left->entry->key)
      {
        pR->left = rotateLeft(pR->left);
        return rotateRight(pR);
      }
    }
    if (key > pR->entry->key)
    {
      // * Zag Zag
      if (key > pR->right->entry->key)
      {
        Node *tmp = rotateLeft(pR);
        return rotateLeft(tmp);
      }
      // * Zag Zig
      if (key < pR->right->entry->key)
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
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::rNLR(void (*func)(K, V), Node *pR)
{
  if (pR == nullptr)
    return;

  (*func)(pR->entry->key, pR->entry->value);

  if (pR->left != nullptr)
    rNLR(func, pR->left);
  if (pR->right != nullptr)
    rNLR(func, pR->right);

  return;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::rClear(Node *pR, bool &deleteEntry)
{
  if (pR == nullptr)
    return;

  rClear(pR->left, deleteEntry);
  rClear(pR->right, deleteEntry);

  if (deleteEntry == true)
    delete pR->entry;
  delete pR;

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
  root = (root == nullptr) ? newNode : rAdd(newNode, root);
  return newNode;
}

template <class K, class V>
void BKUTree<K, V>::AVLTree::remove(K key, bool deleteEntry)
{
  root = rRemove(key, root, nullptr, deleteEntry);
  return;
}

template <class K, class V>
V BKUTree<K, V>::AVLTree::search(K key)
{
  return rSearch(key, root)->entry->value;
}

template <class K, class V>
void BKUTree<K, V>::AVLTree::traverseNLR(void (*func)(K, V))
{
  rNLR(func, root);
  return;
}

template <class K, class V>
void BKUTree<K, V>::AVLTree::clear(bool deleteEntry)
{
  if (root == nullptr)
    return;

  rClear(root, deleteEntry);
  root = nullptr;
  return;
}

template <class K, class V>
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::rAdd(Node *pI, Node *pR)
{
  // *
  if (pR == nullptr)
    return pI;

  // *
  if (pI->entry->key == pR->entry->key)
    throw "Duplicate key";

  if (pI->entry->key < pR->entry->key)
    pR->left = rAdd(pI, pR->left);
  if (pI->entry->key > pR->entry->key)
    pR->right = rAdd(pI, pR->right);

  // *
  pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;

  // *
  if (findBalance(pR) > 1 && findBalance(pR->left) > 0)
  {
    return rotateRight(pR);
  }

  if (findBalance(pR) < -1 && findBalance(pR->right) < 0)
  {
    return rotateLeft(pR);
  }

  if (findBalance(pR) > 1 && findBalance(pR->left) < 0)
  {
    pR->left = rotateLeft(pR->left);
    return rotateRight(pR);
  }

  if (findBalance(pR) < -1 && findBalance(pR->right) > 0)
  {
    pR->right = rotateRight(pR->right);
    return rotateLeft(pR);
  }

  return pR;
}

template <class K, class V>
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::rRemove(K key, Node *pR, Node *pN, bool &deleteEntry)
{
  if (pR == nullptr)
    throw "Not found";

  if (key < pR->entry->key)
    pR->left = rRemove(key, pR->left, pR, deleteEntry);
  else if (key > pR->entry->key)
    pR->right = rRemove(key, pR->right, pR, deleteEntry);
  else
  {
    // * No or one child
    if (pR->left == nullptr || pR->right == nullptr)
    {
      Node *tmp = (pR->left) ? pR->left : pR->right;

      if (pN->left == pR)
        pN->left = tmp;
      else
        pN->right = tmp;

      // * No child
      if (tmp == nullptr)
      {
        tmp = pR;
        pR = nullptr;
      }
      else // * One child
      {
        Node *tmp1 = tmp;
        tmp = pR;
        pR = tmp1;
      }

      if (deleteEntry == true)
        delete tmp->entry;
      else
        tmp->entry = nullptr;

      delete tmp;

      if (pN == nullptr)
      {
        root = pN;
        return pN;
      }
    }
    else // * Two children
    {
      // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=130606#p427519
      Node *cur = pR->left;
      while (cur->right != nullptr)
        cur = cur->right;

      *pR->entry = *cur->entry;
      pR->corr = cur->corr;
      if (pR->corr != nullptr)
        pR->corr->corr = pR;

      pR->left = rRemove(cur->entry->key, pR->left, pR, deleteEntry);
    }
  }

  if (pR == nullptr || pR->entry == nullptr)
    return pR;

  // *
  pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;

  // *
  if (findBalance(pR) > 1 && findBalance(pR->left) > 0)
  {
    return rotateRight(pR);
  }

  if (findBalance(pR) < -1 && findBalance(pR->right) < 0)
  {
    return rotateLeft(pR);
  }

  if (findBalance(pR) > 1 && findBalance(pR->left) < 0)
  {
    pR->left = rotateLeft(pR->left);
    return rotateRight(pR);
  }

  if (findBalance(pR) < -1 && findBalance(pR->right) > 0)
  {
    pR->right = rotateRight(pR->right);
    return rotateLeft(pR);
  }

  return pR;
}

template <class K, class V>
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::rSearch(K key, Node *pR)
{
  if (pR == nullptr)
    throw "Not found";
  if (key == pR->entry->key)
    return pR;
  if (key < pR->entry->key)
    rSearch(key, pR->left);
  if (key > pR->entry->value)
    rSearch(key, pR->right);
  return pR;
}

template <class K, class V>
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::rartedSearch(K key, Node *pR, Node *exitNode, V &rValue, vector<K> &traversedList)
{
  if (pR == nullptr || pR == exitNode)
    throw "Not found";
  if (key == pR->entry->key)
  {
    rValue = pR->entry->value;
    return pR;
  }

  traversedList.push_back(pR->entry->key);
  if (key < pR->entry->key)
    rartedSearch(key, pR->left, exitNode, rValue, traversedList);
  if (key > pR->entry->value)
    rartedSearch(key, pR->right, exitNode, rValue, traversedList);
  return pR;
}

template <class K, class V>
void BKUTree<K, V>::AVLTree::rNLR(void (*func)(K, V), Node *pR)
{
  if (pR == nullptr)
    return;

  (*func)(pR->entry->key, pR->entry->value);

  if (pR->left != nullptr)
    rNLR(func, pR->left);
  if (pR->right != nullptr)
    rNLR(func, pR->right);
  return;
}

template <class K, class V>
void BKUTree<K, V>::AVLTree::rClear(Node *pR, bool &deleteEntry)
{
  if (pR == nullptr)
    return;

  rClear(pR->left, deleteEntry);
  rClear(pR->right, deleteEntry);

  if (deleteEntry == true)
    delete pR->entry;
  delete pR;

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
  int tmp = findHeight(pR->left) - findHeight(pR->right);
  pR->balance = tmp;
  return tmp;
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

#endif
