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
void enter(Author *input);
void enter(book_st *input);
bool validDay(Date *check);
void enterBooks(book_st *&input, int &numberBooks);
int countBooksByType(book_st *input, int numberBooks, char search[30]);
void printTypeBooks(book_st *output, int numberBooks);
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
void enter(book_st *input)
{ 
    //Nhap thong tin cua 1 quyen sach (gom co ham nhap tac gia)
    printf("\nNhap id cua sach: ");
    fflush(stdin);
    scanf("%d", &input->id);
    printf("Ten: ");
    fflush(stdin);
    gets(input->name);
    printf("************** Nhap thong tin tac gia **************");
    input->author = (Author *)malloc(sizeof(Author));
    enter(input->author);
    fflush(stdin);
    printf("\nThe loai: ");
    gets(input->type);
    printf("Gia tien: ");
    scanf("%d", &input->price);
}
void enterBooks(book_st *&input, int &numberBooks)
{ 
    //Nhap thong tin nhieu quyen sach
    do
    {
        printf("->Nhap so cuon sach: ");
        scanf("%d", &numberBooks);
        if (numberBooks <= 0)
        {
            printf("Hay nhap lai !\n");
        }
    } while (numberBooks <= 0);
    input = (book_st *)realloc(input, (numberBooks) * sizeof(book_st));
    for (int index = 0; index < numberBooks; index++) //vong lap de lap ham nhap 1 quyen sach
    {
        printf("\n++++++++++++++++ Nhap thong tin quyen sach %d ++++++++++++++++", index + 1);
        enter(&*(input + index));
    }
}
int countBooksByType(book_st *input, int numberBooks, char search[30])
{
    //dem sach theo the loai
    int count = 0;
    for (int i = 0; i < numberBooks; i++)
    {
        if (strcmp((input + i)->type, search) == 0)
        {
            count++; //neu cung loai thì dem
        }
    }
    return count;
}
void printTypeBooks(book_st *output, int numberBooks)
{ 
    //in so the loai
    if (numberBooks != 0)
    {
        printf("\nTruyen tranh co %d quyen sach", countBooksByType(output, numberBooks, "truyen tranh"));
        printf("\nTruyen kiem hiep co %d quyen sach", countBooksByType(output, numberBooks, "tai lieu"));
        printf("\nGiao trinh co %d quyen sach\n", countBooksByType(output, numberBooks, "giao trinh"));
    }
}
