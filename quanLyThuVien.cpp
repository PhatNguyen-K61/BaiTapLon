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
void editBook(book_st *output, int &id_need_to_find, int numberBooks);
void removeBook(book_st *output, int &id_need_to_find, int &numberBooks);
void enterType(char search[30]);
void addBook(book_st *input, int &numberBooks, const book_st book);
book_st *findBookByType(book_st *input, int numberBooks, int totalBooks, char search[30]);
void print(book_st *output, int numberBooks);
void arrangeBook(book_st *output, int numberBooks);
void exportBook(FILE *file, char *path, book_st *output, int numberBooks);
void menu(FILE *file, char *path, book_st *input, int numberBooks, int totalBooks, char search[30], int id_need_to_find);
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
        printf("\nTai lieu co %d quyen sach", countBooksByType(output, numberBooks, "tai lieu"));
        printf("\nGiao trinh co %d quyen sach\n", countBooksByType(output, numberBooks, "giao trinh"));
    }
}
void editBook(book_st *output, int &id_need_to_find, int numberBooks)
{ 
    //ham sua sach
    int has_book = false;
    printf("Nhap id quyen sach: ");
    scanf("%d", &id_need_to_find);
    for (int index = 0; index < numberBooks; index++)
    {
        if (id_need_to_find == (output + index)->id)
        {
            printf("\n======== Sua thong tin sach ========");
            fflush(stdin);
            printf("\nTen: ");
            gets((output + index)->name);
            printf("******** Nhap thong tin tac gia ********");
            (output + index)->author = (Author *)malloc(sizeof(Author));
            enter((output + index)->author);
            fflush(stdin);
            printf("\nThe loai: ");
            gets((output + index)->type);
            printf("Gia tien: ");
            scanf("%d", &(output + index)->price);
            has_book = true;
        }
    }
    if (has_book)
    {
        printf("Sua sach thanh cong!\n");
    }
    else
    {
        printf("Khong co quyen sach nay !\n");
    }
}
void removeBook(book_st *output, int &id_need_to_find, int &numberBooks)
{ 
    //ham xoa sach
    bool has_book = false;
    printf("Nhap id quyen sach: ");
    scanf("%d", &id_need_to_find);
    for (int index = 0; index < numberBooks; index++)
    {
        if ((output + index)->id == id_need_to_find)
        {
            for(int j = index; j < numberBooks - 1; j++){
                *(output + j) = *(output + j + 1);
                has_book = true;
            }
            numberBooks--;
        }
    }
    if (has_book)
    {
        printf("Xoa sach thanh cong !\n");
    }
    else
    {
        printf("Khong co quyen sach nay !\n");
    }
}
void enterType(char search[30])
{
    printf("\nNhap the loai: ");
    fflush(stdin);
    gets(search);
}
void addBook(book_st *input, int &numberBooks, const book_st book)
{ 
    //them sach
    numberBooks++;
    input = (book_st *)realloc(input, numberBooks * sizeof(book_st));
    *(input + numberBooks - 1) = book;
}
book_st *findBookByType(book_st *input, int numberBooks, int totalBooks, char search[30])
{ 
    //tim sach theo the loai
    book_st *result;
    book_st temp;
    totalBooks = 0;
    result = (book_st *)calloc(totalBooks, sizeof(book_st));
    for (int index = 0; index < numberBooks; index++)
    {
        if (strcmp((input + index)->type, search) == 0)
        {
            temp = *(input + index);
            addBook(result, totalBooks, temp);
        }
    }
    return result;
}
void print(book_st *output, int numberBooks)
{ 
    //ham xuat
    if (numberBooks == 0)
    {
        printf("Loi !!!\n");
    }
    else
    {
        printf("\nId ||Ten\t\t||Tac gia\t\t\t     ||The loai\t\t\t||Gia tien");
        for (int index = 0; index < numberBooks; index++)
        {
            printf("\n%-3d||%-17s\t||%-21s(%-2d/%-2d/%-4d)  ||%-19s\t||%d", (output + index)->id, (output + index)->name, (output + index)->author->name, (output + index)->author->birthday->day, (output + index)->author->birthday->month, (output + index)->author->birthday->year, (output + index)->type, (output + index)->price);
        }
    }
    printf("\n");
}
void arrangeBook(book_st *output, int numberBooks)
{ 
    //sap xep sach
    book_st temp;
    for (int i = 0; i < numberBooks - 1; i++)
    {
        for (int j = i + 1; j < numberBooks; j++)
        {
            if (strcmp((output + i)->type, (output + j)->type) < 0)
            {
                temp = *(output + i);
                *(output + i) = *(output + j);
                *(output + j) = temp;
            }
        }
    }
}
void exportBook(FILE *file, char *path, book_st *output, int numberBooks)
{ 
    //xuat sach ra file
    char *mode = "ab";
    file = fopen(path, mode);
    fprintf(file, "\nId ||Ten\t\t\t\t\t||Tac gia\t\t\t\t\t\t\t\t||The loai\t\t\t\t||Gia tien");
    for (int index = 0; index < numberBooks; index++)
    {
        fprintf(file, "\n%-3d||%-20s\t||%-24s(%-2d/%-2d/%-4d)  ||%-17s\t\t||%d", (output + index)->id, (output + index)->name, (output + index)->author->name, (output + index)->author->birthday->day, (output + index)->author->birthday->month, (output + index)->author->birthday->year, (output + index)->type, (output + index)->price);
    }
    fclose(file);
}
void menu(FILE *file, char *path, book_st *input, int numberBooks, int totalBooks, char search[30], int id_need_to_find)
{ 
    //ham menu
    int choise;
    do
    {
        system("cls");
        printf("\n\t\t\t\t|--------------------------MENU-----------------------|\n");
        printf("\t\t\t\t|1. Nhap du lieu cua tung quyen sach.\t\t      |\n");
        printf("\t\t\t\t|2. Sap xep, thong ke va hien thi thong tin\t      |\n\t\t\t\t|   chi tiet cua tung quyen sach theo the loai (Z->A).|\n");
        printf("\t\t\t\t|3. Sua thong tin sach\t\t\t\t      |\n");
        printf("\t\t\t\t|4. Xoa thong tin sach\t\t\t\t      |\n");
        printf("\t\t\t\t|5. Tim quyen sach theo the loai\t\t      |\n");
        printf("\t\t\t\t|6. Ghi vao tap tin nhi phan book.dat.\t\t      |\n");
        printf("\t\t\t\t|7. Thoat\t\t\t\t\t      |\n");
        printf("\t\t\t\t|-----------------------------------------------------|\n");
        printf("\n--> Lua chon cua ban: ");
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            enterBooks(input, numberBooks);
            system("pause");
            break;
        case 2:
            arrangeBook(input, numberBooks);
            print(input, numberBooks);
            printTypeBooks(input, numberBooks);
            system("pause");
            break;
        case 3:
            editBook(input, id_need_to_find, numberBooks);
            system("pause");
            break;
        case 4:
            removeBook(input, id_need_to_find, numberBooks);
            system("pause");
            break;
        case 5:
            enterType(search);
            print(findBookByType(input, numberBooks, totalBooks, search), countBooksByType(input, numberBooks, search));
            system("pause");
            break;
        case 6:
            exportBook(file, path, input, numberBooks);
            system("pause");
            break;
        case 7:
            break;
        default:
            printf("Hay nhap lai\n");
            system("pause");
            break;
        }
    } while (choise != 7);
}
