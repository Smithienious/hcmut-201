#include <iostream>
#include <string.h>

struct book
{
    book *head;
    book *next;
    char *name;
    int year;

    book()
    {
        this->head = nullptr;
        this->next = nullptr;
        this->name = nullptr;
        this->year = -1;
    }
    book(char *name, int year, book *next = nullptr) : year(year), next(next)
    {
        this->head = head;
        char *newName = new char[strlen(name) + 1];
        strcpy(newName, name);
        this->name = newName;
    }
    ~book()
    {
        book *ptr = this->head;
        book *tmp = ptr;
        while (ptr != nullptr)
        {
            tmp = ptr;
            ptr = ptr->next;
            delete tmp;
        }
    }

    void add(book *head, char *name, int year, int position)
    {
        this->head = head;

        // * Empty list
        if (this->head == nullptr)
        {
            book *newBook = new book(name, year);
            this->head = newBook;
            return;
        }

        // * Pre-list
        if (position == 0)
        {
            book *newBook = new book(name, year);
            newBook->next = this->head;
            this->head = newBook;
            return;
        }

        // * Traverse
        int idx = 0;
        book *ptr = this->head;
        book *tmp = ptr;
        while (ptr->next != nullptr && idx < position)
        {
            tmp = ptr;
            ptr = ptr->next;
            idx += 1;
        }

        // * In-list
        if (idx <= position)
        {
            book *newBook = new book(name, year, ptr);
            tmp->next = newBook;
            return;
        }

        // * Post-list
        book *newBook = new book(name, year);
        ptr->next = newBook;
        return;
    }

    void remove(book *head, int position)
    {
        this->head = head;

        // * Empty list
        if (this->head == nullptr)
            return;

        // * Pre-list
        if (position == 0)
        {
            book *ptr = this->head;
            this->head = this->head->next;
            delete ptr;
            return;
        }

        // * Traverse
        int idx = 0;
        book *ptr = this->head;
        book *tmp = ptr;
        while (ptr->next != nullptr && idx < position)
        {
            tmp = ptr;
            ptr = ptr->next;
            idx += 1;
        }

        // * In-list
        tmp->next = ptr->next;
        delete ptr;
        return;
    }

    void print(book *head)
    {
        this->head = head;
        book *ptr = this->head;

        while (ptr->next != nullptr)
            std::cout << "[" << ptr->name << ", " << ptr->year << "]" << std::endl;
    }
};

int main()
{
    book *Book = new book();

    delete Book;
    return 0;
}