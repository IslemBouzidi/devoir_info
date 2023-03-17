#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include "..\Header\classes.h"
#include "..\Header\functions.h"
#include "..\Header\graphics.h"

// main fonction
int main(void)
{
    // part one, managment of classes and students
    classe *class_tab = NULL;
    student *stu_tab = NULL;

    // creation of one element's table
    class_tab = (classe *)calloc(1, sizeof(classe)); 
    stu_tab = (student *)calloc(1, sizeof(student));

    if (class_tab == NULL || stu_tab == NULL){// error raising
        printf("insufisent storage\n");
        Sleep(2000);
        exit(1);
    }

    //return a full classified table
    class_tab = readlocal(class_tab);
    stu_tab = readeleve(stu_tab);

    if (class_tab == NULL || stu_tab == NULL)exit(1);//error raising: storage_error or _unfound file

    // part two, main manu 

    unsigned char task;
    char run = 1;

    while(run){//infinite loop
        clear();
        main_print();
        task = ask("task");//task is a char
        switch (task){
        case 'S'://sortie
            run = 0;
            break;
        case 'L'://
            local_menu(class_tab);
            break;
        case 'P':
            clear();
            list_print();
            task = ask(task);
            break;
        case 'E':
            break;
        default:
            printf("saisie invalide");
            break;
        } 
        task = 0;
    }

    free(class_tab);
    free(stu_tab);

    return 0;
}


