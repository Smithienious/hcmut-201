/************
 * @file BusParking.hpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief
 * @version 0.1.1
 * @date 2021-01-05
 *
 * @copyright Copyright (c) 2021
 *
 ************/

#include <vector>
#include <algorithm>

using namespace std;

class BusParking
{
public:
  class Interval
  {
  public:
    int start;
    int end;

    Interval(int start = 0, int end = 0) : start(start), end(end) {}

    bool operator==(const Interval &obj)
    {
      return start == obj.start && end == obj.end;
    }
  };

  // * Augmented interval tree
  class IntervalTree
  {
    class Node
    {
      Interval *interval;
      int maxEnd;
      int height;
      Node *left, *right;
      friend class IntervalTree;

    public:
      Node(Interval *i = nullptr, Node *l = nullptr, Node *r = nullptr) : interval(i), maxEnd(i->end), height(1), left(l), right(r) {}

      bool doOverlap(Interval itl)
      {
        return this->interval->start <= itl.end && itl.start <= this->interval->end;
      }
    }; // class Node

  public:
    Node *root;

    IntervalTree() : root(nullptr) {}
    ~IntervalTree() { this->clear(root); }

    int add(Interval *interval)
    {
      if (root == nullptr)
      {
        root = new Node(interval);
        return 1;
      }

      root = rAdd(interval, root);
      return oSearch(*interval, root);
    }

    Node *rAdd(Interval *interval, Node *pR)
    {
      if (pR == nullptr)
        return new Node(interval);

      if (interval->start < pR->interval->start)
        pR->left = rAdd(interval, pR->left);
      else
        pR->right = rAdd(interval, pR->right);

      pR->height = findMax(getHeight(pR->left), getHeight(pR->right)) + 1;

      if (getBalance(pR) > 1 && getBalance(pR->left) > 0)
      {
        return rotateRight(pR);
      }

      if (getBalance(pR) < -1 && getBalance(pR->right) < 0)
      {
        return rotateLeft(pR);
      }

      if (getBalance(pR) > 1 && getBalance(pR->left) < 0)
      {
        pR->left = rotateLeft(pR->left);
        return rotateRight(pR);
      }

      if (getBalance(pR) < -1 && getBalance(pR->right) > 0)
      {
        pR->right = rotateRight(pR->right);
        return rotateLeft(pR);
      }

      return pR;
    }

    Node *remove(Interval itl, Node *pR, Node *pN)
    {
      if (pR == nullptr)
        return pR;

      if (itl.start < pR->interval->start)
        pR->left = remove(itl, pR->left, pR);
      else if (itl.start > pR->interval->start)
        pR->right = remove(itl, pR->right, pR);
      else
      {
        // * No child
        if (pR->left == nullptr && pR->right == nullptr)
        {
          if (pN != nullptr)
          {
            if (pN->left == pR)
              pN->left = nullptr;
            else
              pN->right = nullptr;
          }

          delete pR->interval;
          delete pR;
          pR = nullptr;

          if (pN == nullptr)
          {
            root = pN;
            return pN;
          }

          return nullptr;
        }
        // * Left child
        else if (pR->right == nullptr)
        {
          Node *tmp = pR->left;

          if (pN != nullptr)
          {
            if (pN->left == pR)
              pN->left = tmp;
            else
              pN->right = tmp;
          }

          delete pR->interval;
          delete pR;
          pR = nullptr;

          if (pN == nullptr)
          {
            root = pN;
            return pN;
          }

          return tmp;
        }
        // * Right child
        else if (pR->left == nullptr)
        {
          Node *tmp = pR->right;

          if (pN != nullptr)
          {
            if (pN->left == pR)
              pN->left = tmp;
            else
              pN->right = tmp;
          }

          delete pR->interval;
          delete pR;
          pR = nullptr;

          if (pN == nullptr)
          {
            root = pN;
            return pN;
          }

          return tmp;
        }
        else // * Two children
        {
          Node *cur = pR->left, *par = cur;
          while (cur->right != nullptr)
          {
            par = cur;
            cur = cur->right;
          }

          if (pN != nullptr)
          {
            if (pN->left == pR)
              pN->left = cur;
            else
              pN->right = cur;
          }

          Node *tmp = cur->left;

          if (par == cur)
          {
            cur->left = pR;
            cur->right = pR->right;
            pR->left = tmp;
            pR->right = nullptr;
          }
          else
          {
            cur->left = pR->left;
            cur->right = pR->right;
            pR->left = tmp;
            pR->right = nullptr;
            par->right = pR;
          }

          tmp = cur;
          cur = pR;
          pR = tmp;

          pR->left = remove(itl, pR->left, pR);
        }
      }

      if (pR == nullptr)
        return pR;

      // *
      pR->height = findMax(getHeight(pR->left), getHeight(pR->right)) + 1;

      // *
      if (getBalance(pR) > 1 && getBalance(pR->left) > 0)
      {
        return rotateRight(pR);
      }

      if (getBalance(pR) < -1 && getBalance(pR->right) < 0)
      {
        return rotateLeft(pR);
      }

      if (getBalance(pR) > 1 && getBalance(pR->left) < 0)
      {
        pR->left = rotateLeft(pR->left);
        return rotateRight(pR);
      }

      if (getBalance(pR) < -1 && getBalance(pR->right) > 0)
      {
        pR->right = rotateRight(pR->right);
        return rotateLeft(pR);
      }

      return pR;
    }

    void clear(Node *pR)
    {
      if (pR == nullptr)
        return;

      clear(pR->left);
      clear(pR->right);

      delete pR->interval;
      delete pR;

      return;
    }

    int oSearch(Interval itl, Node *pR)
    {
      if (pR == nullptr)
        return 0;

      int overlap = 0;
      if (pR->doOverlap(itl))
        overlap += 1;

      if (pR->left != nullptr && itl.start <= pR->left->maxEnd)
        overlap += oSearch(itl, pR->left);
      if (pR->right != nullptr && itl.end >= pR->right->interval->start)
        overlap += oSearch(itl, pR->right);

      return overlap;
    }

    int findMax(int a, int b)
    {
      return (a > b) ? a : b;
    }

    int getMaxEnd(Node *pR)
    {
      int max = findMax((pR->left) ? pR->left->maxEnd : 0, (pR->right) ? pR->right->maxEnd : 0);
      pR->maxEnd = findMax(max, pR->maxEnd);
      return pR->maxEnd;
    }

    int getHeight(Node *pR)
    {
      if (pR == nullptr)
        return 0;
      return pR->height;
    }

    int getBalance(Node *pR)
    {
      if (pR == nullptr)
        return 0;
      return getHeight(pR->left) - getHeight(pR->right);
    }

    Node *rotateLeft(Node *pR)
    {
      Node *tmp = pR->right;

      pR->right = tmp->left;
      tmp->left = pR;

      pR->height = findMax(getHeight(pR->left), getHeight(pR->right)) + 1;
      tmp->height = findMax(getHeight(tmp->left), getHeight(tmp->right)) + 1;

      getMaxEnd(pR);
      getMaxEnd(tmp);

      return tmp;
    }

    Node *rotateRight(Node *pR)
    {
      Node *tmp = pR->left;

      pR->left = tmp->right;
      tmp->right = pR;

      pR->height = findMax(getHeight(pR->left), getHeight(pR->right)) + 1;
      tmp->height = findMax(getHeight(tmp->left), getHeight(tmp->right)) + 1;

      getMaxEnd(pR);
      getMaxEnd(tmp);

      return tmp;
    }
  }; // class IntervalTree

private:
  IntervalTree *iTree;
  int minParkValue;

public:
  BusParking() : iTree(nullptr), minParkValue(0) {}
  ~BusParking() { this->clear(); }

  void add(int s, int t)
  {
    if (iTree == nullptr)
      iTree = new IntervalTree();

    Interval *newInterval = new Interval(s, t);
    int tmp = iTree->add(newInterval);
    if (tmp > minParkValue)
      minParkValue = tmp;

    return;
  }

  void remove(int s, int t)
  {
    if (iTree == nullptr)
      return;
    iTree->remove(Interval(s, t), iTree->root, nullptr);
  }

  void clear()
  {
    if (iTree == nullptr)
      return;
    iTree->clear(iTree->root);

    return;
  }

  int minPark()
  {
    return minParkValue;
  }
}; // class BusParking