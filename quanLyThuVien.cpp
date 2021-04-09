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
int main()
{
    FILE *file;
    char *output_path = "./src/baiTapLon/book.dat";
    book_st *bookList;
    int numberBooks = 0;
    int totalBooks;
    char search[30];
    int id_need_to_find;
    bookList = (book_st *)malloc(sizeof(book_st));
    system("color b0");
    menu(file, output_path, bookList, numberBooks, totalBooks, search, id_need_to_find);
    if(bookList != NULL){
        free(bookList);
    }
    return EXIT_SUCCESS;
}
bool validDay(Date *check)
{
    //kiểm tra ngày tháng
    bool validDay = true;
    if (check->month < 0 || check->month > 12)
    {
        validDay = false;
    }
    else
    {
        switch (check->month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (check->day < 1 || check->day > 31)
            {
                validDay = false;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (check->day < 1 || check->day > 30)
            {
                validDay = false;
            }
            break;
        case 2:
            if (check->year % 4 == 0 && check->day < 1 || check->day > 29)
            {
                validDay = false;
            }
            break;
        }
    }
    return validDay;
}
void enter(Date *input)
{ //Nhap ngay thang nam
    printf("\nNgay: ");
    scanf("%d", &input->day);
    printf("Thang: ");
    scanf("%d", &input->month);
    do{
    printf("Nam: ");
    scanf("%d", &input->year);
    if(input->year > 2021 || input->year <= 0){
        printf("*Nhap lai nam sinh*\n");
    }
    }while(input->year > 2021 || input->year <= 0);
}
void enter(Author *input)
{
    //Nhap thong tin tac gia (gom co ham nhap ngay thang nam)
    printf("\nNhap ten tac gia: ");
    gets(input->name);
    printf("-------- Nhap ngay thang nam sinh tac gia --------");
    do
    {
        input->birthday = (Date *)malloc(sizeof(Date));
        enter(input->birthday);
        if(!validDay(input->birthday)){
            printf("- Hay nhap lai!");
        }
    } while (!validDay(input->birthday));
}
