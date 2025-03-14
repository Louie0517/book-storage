#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record{
    char bookTitle[100];
    char author[100];
    int yearPublished;
}record;

record rec[100];
int size = 0, duplicate = 0;

int add(int *size);
int display(int *size);
int del(int *size);
int menu();

int main(){

    menu();

    return 0;
}

int add(int *size){
    FILE *file;
    record temporary;
    int isFilled = 0;
    file = fopen("Library depot.txt", "a");

    if(file == NULL){
        printf("There is no file exist");
        return -1;
    }

    if(*size < 100){
                printf("Enter the book title: ");
                scanf(" %[^\n]", rec[*size].bookTitle);
                printf("Enter the author name: ");
                scanf(" %[^\n]", rec[*size].author);
                printf("Enter the year book was published: ");
                scanf("%i", &rec[*size].yearPublished);

    for(int i = 0; i < *size - 1; i++){
        for(int j = 0; j < *size - i - 1; j++){
            if(strcmp(rec[j].bookTitle, rec[j+1].bookTitle) > 0){
                temporary = rec[j];
                rec[j] = rec[j+1];
                rec[j+1] = temporary;
            }
        }
    }
        for(int i = 0; i < *size; i++){
            if(strcmp(rec[i].bookTitle, rec[*size - 1].bookTitle) == 0){
                duplicate = 1;
                printf("It has a record already.");
                fclose(file);
                return 1;
            }
        }

        fprintf(file, "Book Title: %s\nBook Author: %s\nYear Published: %i\n", rec[*size].author, rec[*size].bookTitle, rec[*size].yearPublished);
        (*size)++;
    } else {
        printf("Record is full.");
    }
    system("cls");
    fclose(file);
    return 0;
}

int display(int *size){
    int isExist = 0;

   while(!isExist){
        if(*size == 0){
            printf("There is no record...\n");
            return -1;
        }
        printf("Book Tile\t\tAuthor\tPublished Year\n");
        for(int i = 0; i < *size; i++) {
            printf("%s\t\t%s\t%i\n", rec[i].bookTitle, rec[i].author, rec[i].yearPublished);
        }
        isExist = 1;
        return 0;
   }
}

int del(int *size){
    char bookTitle[100];
    int isFound = 0;

    if(*size == 0){
            printf("There is no record to delete...\n");
            return -1;
        }

    printf("Enter the book title to delete: ");
    scanf(" %[^\n]", bookTitle);

    for(int i = 0; i < *size; i++){
        if(strcmp(rec[i].bookTitle, bookTitle) == 0){
            isFound = 1;

            for(int j = i; j < *size - 1; j++){
                rec[j] = rec[j+1];
            }
            (*size)--;
            printf("book has been deleted.\n");
            return 1;
        }
    } system("cls");

    if(!isFound){
        printf("Book can not found.");
        return -1;
    }
    return 0;

}

int menu(){
    int isDone = 0;
    printf("Welcome to Book Repository\n\n");

    while(!isDone){
        char choice;
        printf("Enter 'A' Add");
        printf("\n");
        printf("Enter 'R' Records");
        printf("\n");
        printf("Enter 'D' Delete");
        printf("\n");
        printf("Enter 'E' Exit");
        printf("\n");
        printf("Type your choice to perform: ");
        scanf(" %c", &choice);
            switch(choice){
                case 'A': case 'a':
                    system("cls");
                    add(&size);
                    break;
                case 'R': case 'r':
                    system("cls");
                    display(&size);
                    break;
                case 'D': case 'd':
                    system("cls");
                    del(&size);
                    break;
                case 'E': case 'e':
                    exit(1);
                    isDone = 1;
                default:
                    system("cls");
                    printf("\nWrong input.\n\n");
            }
        }
    return 0;
}
