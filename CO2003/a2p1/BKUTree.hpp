/************
 * @file BKUTree.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main implementation for Assignment 2 Phase 1
 *
 * Learners are expected to be able to use BST, specifically AVL and Splay Tree
 * AVL tree stores the BST structure, Splay tree stores recently accessed elements
 *
 * @version 0.4.0
 * @date 2020-12-19
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
  queue<K> keys;
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

    void tree(string, Node *, bool);
    Node *recursiveSearch(K, Node *, int &);
    Node *retardedSearch(K, Node *, int &, Node *, vector<K> &, bool &, V &);
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

    void tree(string, Node *, bool);
    Node *recursiveSearch(K, Node *pR, Node *exitNode = nullptr);
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
  avlNode->corr = splayNode;
  splayNode->corr = avlNode;
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
      splay->root = splay->retardedSearch(key, splay->root, i, splay->root, traversedList, splayed, rValue);
      return rValue;
    }
  }

  // * 3a. Get Splay root in AVL
  typename AVLTree::Node *splay2avl = splay->root->corr;
  typename AVLTree::Node *avlNode = splay->root->corr;

  // * 3b. Try searching on AVL from Splay root in AVL. If found -> return key, else continue
  try
  {
    // * 3c.
    avlNode = avl->recursiveSearch(key, splay2avl);
  }
  catch (...)
  {
    // * 3d. Try searching on AVL from root. If node equals corresponding AVL node or not found -> throw not found, else continue
    avlNode = avl->recursiveSearch(key, avl->root, splay2avl);
  }

  // * 3e. With node found in AVL, splay Splay tree at AVL->corr
  typename SplayTree::Node *avl2splay = avlNode->corr;
  int i = 0;
  bool splayed = false;
  V rValue;
  splay->root = splay->retardedSearch(key, avl2splay, i, splay->root, traversedList, splayed, rValue);

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
  avl->clear();
  splay->clear(false);
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
void BKUTree<K, V>::SplayTree::remove(K key, bool deleteEntry)
{
  int i = 0;
  root = recursiveSearch(key, root, i);

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
    root = recursiveSearch(tmpKey, root, i);
    root->right = exRoot->right;

    if (deleteEntry == true)
      delete exRoot->entry;
    delete exRoot;
  }
}

template <class K, class V>
V BKUTree<K, V>::SplayTree::search(K key)
{
  int i = 0;
  root = recursiveSearch(key, root, i);
  return root->entry->value;
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
void BKUTree<K, V>::SplayTree::clear(bool deleteEntry)
{
  function<void(Node *, bool &)> recursiveClear = [&](Node *pR, bool &deleteEntry) {
    if (pR != nullptr)
    {
      recursiveClear(pR->left, deleteEntry);
      recursiveClear(pR->right, deleteEntry);
      if (deleteEntry == true)
        delete pR->entry;
      pR->left = pR->right = nullptr;
      if (pR == root)
        root = nullptr;
      delete pR;
    }
  };

  recursiveClear(root, deleteEntry);
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
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::recursiveSearch(K key, Node *pR, int &relativeHeight)
{
  if (pR == nullptr)
    throw "Not found";
  if (key == pR->entry->key)
  {
    relativeHeight = 1;
    return pR;
  }
  if (key < pR->entry->key)
    pR->left = recursiveSearch(key, pR->left, relativeHeight);
  if (key > pR->entry->value)
    pR->right = recursiveSearch(key, pR->right, relativeHeight);

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
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::retardedSearch(K key, Node *pR, int &relativeHeight, Node *relativeRoot, vector<K> &traversedList, bool &splayed, V &rValue)
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
    pR->left = retardedSearch(key, pR->left, relativeHeight, relativeRoot, traversedList, splayed, rValue);
  if (key > pR->entry->value)
    pR->right = retardedSearch(key, pR->right, relativeHeight, relativeRoot, traversedList, splayed, rValue);

  if (splayed == false)
  {
    splayed = true;

    if (pR == relativeRoot && relativeHeight == 1)
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
  }

  return pR;
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
void BKUTree<K, V>::AVLTree::remove(K key, bool deleteEntry)
{
  function<Node *(K, Node *, Node *, bool &)> recursiveDelete = [&](K key, Node *pR, Node *pN, bool &deleteEntry) {
    if (pR == nullptr)
      throw "Not found";

    if (key < pR->entry->key)
      pR->left = recursiveDelete(key, pR->left, pR, deleteEntry);
    else if (key > pR->entry->key)
      pR->right = recursiveDelete(key, pR->right, pR, deleteEntry);
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
        delete tmp;

        if (pN == nullptr)
          return pN;
      }
      else // * Two children
      {
        // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=130606#p427519
        Node *cur = pR->left, *par = cur;
        while (cur->right != nullptr)
        {
          par = cur;
          cur = cur->right;
        }

        Node tmp = *pR;
        pR->left = cur->left;
        pR->right = cur->right;
        cur->right = tmp.right;

        if (par == cur)
        {
          cur->left = pR;
        }
        else
        {
          cur->left = par;
          par->right = pR;
        }

        if (pN->left == pR)
          pN->left = cur;
        else
          pN->right = cur;

        cur->left = recursiveDelete(pR->entry->key, cur->left, cur, deleteEntry);
      }
    }

    if (pR == nullptr || pR->entry == nullptr)
      return pR;

    // *
    pR->height = MAX(findHeight(pR->left), findHeight(pR->right)) + 1;

    // *
    pR->balance = findBalance(pR);

    if (pR->balance > 1 && pR->left->balance >= 0)
    {
      return rotateRight(pR);
    }

    if (pR->balance < -1 && pR->right->balance <= 0)
    {
      return rotateLeft(pR);
    }

    if (pR->balance > 1 && pR->left->balance < 0)
    {
      pR->left = rotateLeft(pR->left);
      return rotateRight(pR);
    }

    if (pR->balance < -1 && pR->right->balance > 0)
    {
      pR->right = rotateRight(pR->right);
      return rotateLeft(pR);
    }

    return pR;
  };

  root = recursiveDelete(key, root, nullptr, deleteEntry);
  return;
}

template <class K, class V>
V BKUTree<K, V>::AVLTree::search(K key)
{
  return recursiveSearch(key)->entry->value;
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
void BKUTree<K, V>::AVLTree::clear(bool deleteEntry)
{
  function<void(Node *, bool &)> recursiveClear = [&](Node *pR, bool &deleteEntry) {
    if (pR != nullptr)
    {
      recursiveClear(pR->left, deleteEntry);
      recursiveClear(pR->right, deleteEntry);
      if (deleteEntry == true)
        delete pR->entry;
      pR->left = pR->right = nullptr;
      if (pR == root)
        root = nullptr;
      delete pR;
    }
  };

  recursiveClear(root, deleteEntry);
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
typename BKUTree<K, V>::AVLTree::Node *BKUTree<K, V>::AVLTree::recursiveSearch(K key, Node *pR, Node *exitNode)
{
  if (pR == nullptr || pR == exitNode)
    throw "Not found";
  if (key == pR->entry->key)
    return pR;
  if (key < pR->entry->key)
    recursiveSearch(key, pR->left, exitNode);
  if (key > pR->entry->value)
    recursiveSearch(key, pR->right, exitNode);
  return pR;
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
