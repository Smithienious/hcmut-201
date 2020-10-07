#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T &element) = 0;
    virtual void add(int index, const T &element) = 0;
    virtual T &removeAt(int index) = 0;
    virtual bool removeItem(const T &item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T &get(int index) = 0;
    virtual void set(int index, const T &element) = 0;
    virtual int indexOf(const T &item) = 0;
    virtual bool contains(const T &item) = 0;
    virtual string toString() = 0;
};

#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = nullptr;
        this->fragmentPointers[1] = nullptr;
    }
    virtual ~FragmentLinkedList();
    virtual void add(const T &element);
    virtual void add(int index, const T &element);
    virtual T &removeAt(int index);
    virtual bool removeItem(const T &item);
    virtual bool empty();
    virtual int size();
    virtual void clear();
    virtual T &get(int index);
    virtual void set(int index, const T &element);
    virtual int indexOf(const T &item);
    virtual bool contains(const T &item);
    virtual string toString();
    Iterator begin(int index = 0);
    Iterator end(int index = -1);

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            this->next = nullptr;
            this->prev = nullptr;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;

    public:
        Iterator(FragmentLinkedList<T> *pList = nullptr, bool begin = true);
        Iterator(FragmentLinkedList<T> *pList = nullptr, int fragmentIndex = 0, bool begin = true);
        Iterator &operator=(const Iterator &iterator);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        void set(const T &element);
        Iterator &operator++();
        Iterator operator++(int);
    };
};

// * Destructor
template <class T>
FragmentLinkedList<T>::~FragmentLinkedList()
{
    if (empty())
        return;

    this->count = 0;
    this->fragmentMaxSize = 0;

    Node *ptr = this->fragmentPointers[0];
    Node *tmp = nullptr;

    while (ptr != nullptr)
    {
        tmp = ptr;
        ptr = ptr->next;
        delete tmp;
    }
}

// * Add a new element into the end of the list
template <class T>
void FragmentLinkedList<T>::add(const T &element)
{
    if (empty())
    {
        Node *newNode = new Node(element, nullptr, nullptr);
        this->fragmentPointers[0] = newNode;

        this->count += 1;
        return;
    }

    Node *ptr = this->fragmentPointers[0];
    while (ptr->next != nullptr)
        ptr = ptr->next;

    Node *newNode = new Node(element, nullptr, ptr);
    ptr->next = newNode;

    this->count += 1;
    return;
}

// * Add a new element into index position
template <class T>
void FragmentLinkedList<T>::add(int index, const T &element)
{
    if (empty())
    {
        Node *newNode = new Node(element, nullptr, nullptr);
        this->fragmentPointers[0] = newNode;
        this->count += 1;
        return;
    }

    if (index <= 0)
    {
        Node *newNode = new Node(element, this->fragmentPointers[0], nullptr);
        this->fragmentPointers[0]->prev = newNode;
        this->fragmentPointers[0] = newNode;
    }
    else if (index >= this->count)
    {
        add(element);
        this->count -= 1;
    }
    else
    {
        Node *ptr = this->fragmentPointers[0];
        int pos = 0;
        while (pos < index - 1)
        {
            ptr = ptr->next;
            pos += 1;
        }

        Node *tmp = ptr->next;
        Node *newNode = new Node(element, tmp, ptr);
        ptr->next = newNode;
        tmp->prev = newNode;
    }

    this->count += 1;
    return;
}

// * Delete the element at index position and return that element
template <class T>
T &FragmentLinkedList<T>::removeAt(int index)
{
    if (empty() || index < 0 || index > this->count - 1)
        throw out_of_range("The index is out of range!");

    Node *ptr = this->fragmentPointers[0];

    if (index == 0)
    {
        this->fragmentPointers[0]->next->prev = nullptr;
        this->fragmentPointers[0] = this->fragmentPointers[0]->next;
    }
    else if (index == this->count - 1)
    {
        while (ptr->next != nullptr)
            ptr = ptr->next;

        ptr->prev->next = nullptr;
        ptr->prev = nullptr;
    }
    else
    {
        int pos = 0;
        while (pos < index)
        {
            ptr = ptr->next;
            pos += 1;
        }

        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
    }

    /*
    this->count -= 1;
    Node tmp = Node(ptr->data, nullptr, nullptr);
    delete ptr;
    return tmp.data;
    */

    // ! Potential memory leak
    return ptr->data;
}

// * Delete the element has value item and return whether that element can be found
template <class T>
bool FragmentLinkedList<T>::removeItem(const T &element)
{
    if (empty())
    {
        this->count -= 1;
        return false;
    }

    Node *ptr = this->fragmentPointers[0];

    if (this->fragmentPointers[0]->data == element)
    {
        this->fragmentPointers[0] = this->fragmentPointers[0]->next;
        this->fragmentPointers[0]->prev = nullptr;
        delete ptr;

        this->count -= 1;
        return true;
    }

    while (ptr->next != nullptr)
    {
        ptr = ptr->next;

        if (ptr->data == element)
        {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            delete ptr;

            this->count -= 1;
            return true;
        }
    }

    return false;
}

// * Checking whether the list is empty
template <class T>
bool FragmentLinkedList<T>::empty()
{
    return this->count < 1;
}

// * Return the size (the number of elements) of the current list
template <class T>
int FragmentLinkedList<T>::size()
{
    return this->count;
}

// * Delete all current elements in the list
template <class T>
void FragmentLinkedList<T>::clear()
{
    this->~FragmentLinkedList();

    return;
}

// * Find and return the element at index position
template <class T>
T &FragmentLinkedList<T>::get(int index)
{
    if (empty() || index < 0 || index > this->count - 1)
        throw out_of_range("The index is out of range!");

    Node *ptr = this->fragmentPointers[0];
    int pos = 0;

    while (pos < index)
    {
        ptr = ptr->next;
        pos += 1;
    }

    return ptr->data;
}

// *
template <class T>
void FragmentLinkedList<T>::set(int index, const T &element)
{
    if (empty() || index < 0 || index > this->count - 1)
        return;

    Node *ptr = this->fragmentPointers[0];
    int pos = 0;

    while (pos < index)
    {
        ptr = ptr->next;
        pos += 1;
    }

    ptr->data = element;

    return;
}

// * Find and return the position of the element which has value item in the list
template <class T>
int FragmentLinkedList<T>::indexOf(const T &item)
{
    if (empty())
        return -1;

    if (this->fragmentPointers[0]->data == item)
        return 0;

    Node *ptr = this->fragmentPointers[0];
    int pos = 0;
    while (ptr->next != nullptr)
    {
        ptr = ptr->next;
        pos += 1;

        if (ptr->data == item)
            return pos;
    }

    return -1;
}

// * Check whether the list contains element that has value item
template <class T>
bool FragmentLinkedList<T>::contains(const T &item)
{
    if (empty())
        return false;

    Node *ptr = this->fragmentPointers[0];

    if (ptr->data == item)
        return true;

    while (ptr->next != nullptr)
    {
        ptr = ptr->next;

        if (ptr->data == item)
            return true;
    }

    return false;
}

// * Return the list in the form of string
template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];

    if (this->count == 0)
        ss << "]";
    else
    {
        ss << ptr->data;

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
            ss << ", " << ptr->data;
        }

        ss << "]";
    }

    return ss.str();
}

// Return the first Iterator corresponding to fragmentIndex
template <typename T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::begin(int index)
{
    // TODO
}

// Return the last Iterator corresponding to fragmentIndex
// With fragmentIndex = -1, return Iterator corresponding to the last element
template <typename T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::end(int index)
{
    // TODO
}

// Constructor with defaults: *pList = nullptr, begin = true
template <typename T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, bool begin)
{
    if (begin)
    {
        this->pList = pList;
        this->pNode = pList->fragmentPointers[0];
    }
}

// Constructor with defaults: *pList = nullptr, fragmentIndex = 0, begin = true
template <typename T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, int fragmentIndex, bool begin)
{
    // TODO
}

// Copy constructor
template <typename T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
    // TODO
}

// Dereference operator
template <typename T>
T &FragmentLinkedList<T>::Iterator::operator*()
{
    return this->data;
}

// Comparison operator
template <typename T>
bool FragmentLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
    // TODO
}

// Pop iterator
template <typename T>
void FragmentLinkedList<T>::Iterator::remove()
{
    if (this->pNode == nullptr)
        return;
}

//
template <typename T>
void FragmentLinkedList<T>::Iterator::set(const T &element)
{
    // TODO
}

// Pre-fix increment operator
template <typename T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator++()
{
    this->pNode = this->pNode->next;
    return this;
}

// Post-fix increment operator
template <typename T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::Iterator::operator++(int)
{
    Iterator i(this);
    this->pNode = this->pNode->next;
    return i;
}

#endif
// END: STUDENT ANSWER

int main()
{
    FragmentLinkedList<int> fList;

    for (int i = 0; i < 20; i++)
        fList.add(i, i * i);

    /*
    for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
        cout << *it << " ";
    cout << endl;
    */

    cout << fList.removeAt(11) << endl;
    cout << fList.toString() << endl;
    return 0;
}
