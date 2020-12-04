#include <iostream>
#include <string.h>

class CharQueue
{
public:
    class Node;
    void enqueue(char data);
    void dequeue();
    char *first();

private:
    Node *head;
    Node *tail;

public:
    CharQueue()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

public:
    class Node
    {
    private:
        char *data;
        Node *next;

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

        Node &operator=(const Node &element)
        {
            data = element.data;
            next = element.next;
            return *this;
        }
    };
};

void CharQueue::enqueue(char data)
{
    // TODO
}

void CharQueue::dequeue()
{
    // TODO
}

char *CharQueue::first()
{
    // TODO
}

int main(int, char **)
{
    std::cout << "Hello, world!\n";
}
