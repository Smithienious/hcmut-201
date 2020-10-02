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

    friend bool checkAuthor(Book book, const char *author)
    {
        /*
         * STUDENT ANSWER
         * TODO: returns true if the author is on the book's authors list, otherwise it returns false
         */
        char *token;
        token = strtok(book.authors, ",");

        while (token != NULL)
        {
            char authors[100];
            if (token[0] == ' ')
                token++;

            strcpy(authors, token);
            if (strcmp(authors, author) == 0)
                return true;

            token = strtok(NULL, ",");
        }

        return false;
    }
};

int main()
{
    Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    cout << checkAuthor(book1, "Nguyen Thi Xuan Anh");
    return 0;
}