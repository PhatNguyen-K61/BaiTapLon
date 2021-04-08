#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
struct Date
{
    int day;
    int month;
    int year;
};
struct Author
{
    char name[30];
    Date *birthday;
};
struct book_st
{
    int id;
    char name[30];
    Author *author;
    char type[30];
    int price;
};
void enter(Date *input);
bool validDay(Date *check);
void enter(book_st *input);
void enter(Author *input);
void enterBooks(book_st *&input, int &numberBooks);
void addBook(book_st *input, int &numberBooks, const book_st book);
void enterType(char search[30]);
void printTypeBooks(book_st *output, int numberBooks);
void editBook(book_st *output, int &id_need_to_find, int numberBooks);
void removeBook(book_st *output, int &id_need_to_find, int &numberBooks);
book_st *findBookByType(book_st *input, int numberBooks, int totalBooks, char search[30]);
int countBooksByType(book_st *input, int numberBooks, char search[30]);
void print(book_st *output, int numberBooks);
void arrangeBook(book_st *output, int numberBooks);
void exportBook(FILE *file, char *path, book_st *output, int numberBooks);
void menu(FILE *file, char *path, book_st *input, int numberBooks, int totalBooks, char search[30], int id_need_to_find);
