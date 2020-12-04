#include <iostream>
#include <string.h>

class Stack
{
public:
    class Node;
    void push(char data);
    void pop();
    char *top();

protected:
    Node *head;

public:
    Stack()
    {
        this->head = nullptr;
    }

public:
    class Node
    {
    private:
        char *data;
        Node *next;
        friend class Stack;

    public:
        Node()
        {
            this->data = nullptr;
            this->next = nullptr;
        }
        Node(char *data, Node *next)
        {
            this->data = new char[strlen(data) + 1];
            strcpy(this->data, data);
            this->next = next;
        }

        Node &operator=(Node const &element)
        {
            this->data = element.data;
            this->next = element.next;
            return *this;
        }
    };
};

void Stack::push(char data)
{
    char *pData = new char[2];
    pData[0] = data;
    pData[1] = '\0';
    Node *newNode = new Node(pData, head);
    head = newNode;
}

void Stack::pop()
{
    if (!head)
        return;

    Node *tmpNode = head;
    head = head->next;
    delete tmpNode;
}

char *Stack::top()
{
    if (!head)
        return nullptr;

    return head->data;
}

int main(int argc, char **argv)
{
    Stack newStack;
    newStack.push('9');
    newStack.push('(');
    std::cout << newStack.top() << std::endl;
    newStack.pop();
    std::cout << newStack.top() << std::endl;
    std::cout << "Hello, world!\n";
}
