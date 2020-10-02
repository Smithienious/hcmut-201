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

    Book(const Book &book)
    {
        /*
         * STUDENT ANSWER
         * TODO: deep copy constructor
         */
        this->title = new char[strlen(book.title) + 1];
        strcpy(this->title, book.title);

        this->authors = new char[strlen(book.authors) + 1];
        strcpy(this->authors, book.authors);

        this->publishingYear = book.publishingYear;
    }

    void setTitle(const char *title)
    {
        /*
         * STUDENT ANSWER
         */
        delete[] this->title;

        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);

        return;
    }

    void setAuthors(const char *authors)
    {
        /*
         * STUDENT ANSWER
         */
        delete[] this->authors;

        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);

        return;
    }

    void setPublishingYear(int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->publishingYear = publishingYear;
    }

    char *getTitle() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->title;
    }

    char *getAuthors() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->authors;
    }

    int getPublishingYear() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->publishingYear;
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

    void printBook()
    {
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
        return;
    }
};

int main()
{
    Book book1("Giai tich 1", "Nguyen Dinh Huy", 2000);
    Book book2 = book1;
    book2.printBook();

    return 0;
}