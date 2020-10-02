#include <bits/stdc++.h>

using namespace std;

class Book
{
private:
    char *title;
    char *authors;
    int publishingYear;

public:
    Book()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero publishingYear and null pointer
         */
        this->title = nullptr;
        this->authors = nullptr;
        this->publishingYear = 0;
    }

    Book(const char *title, const char *authors, int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);

        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);

        this->publishingYear = publishingYear;
    }

    ~Book()
    {
        /*
         * STUDENT ANSWER
         */
        delete[] this->title;
        this->title = nullptr;

        delete[] this->authors;
        this->authors = nullptr;

        this->publishingYear = 0;
    }

    friend class Printer;
};

class Printer
{
public:
    static void printBook(const Book book)
    {
        /*
         * STUDENT ANSWER
         */
        cout << book.title << endl;

        char *ptr = strtok(book.authors, ",");
        while (ptr != nullptr)
        {
            if (ptr[0] == ' ')
                ptr++;
            cout << ptr << endl;
            ptr = strtok(NULL, ",");
        }

        cout << book.publishingYear << endl;
    }
};

int main()
{
    Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    Printer::printBook(book1);
    return 0;
}