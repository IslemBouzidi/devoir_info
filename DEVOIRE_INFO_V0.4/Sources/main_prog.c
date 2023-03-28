#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include "..\Header\classes.h"
#include "..\Header\functions.h"
#include "..\Header\graphics.h"

// main fonction
int main(void)
{
    // declarations
    classe *class_tab = NULL;
    student *stu_tab = NULL;
    affectation *affect_tab = NULL;
    emplacement *emp_tab = NULL;
    unsigned char task,run = 1, bool_local = 1;

    // creation of one element's table
    class_tab = (classe *)calloc(1, sizeof(classe)); 
    stu_tab = (student *)calloc(1, sizeof(student));
    affect_tab = (affectation *)calloc(1, sizeof(affectation));
    emp_tab =(emplacement *)calloc(1 , sizeof(emplacement));

    // error raising
    if (class_tab == NULL || stu_tab == NULL || affect_tab == NULL || emp_tab == NULL){
        printf("insufisent storage\n");
        exit(1);
    }

    //return a full classified table i have to take this part off
    stu_tab = readeleve(stu_tab);

    //infinite loop /main menu
    while(run){

        clear();
        main_print();
        task = ask("task");//task is a char

        switch (task){

        case 'S'://sortie
            run = 0;
            break;

        case 'L'://local
            //reading local.txt for the first time
            if (bool_local){
                class_tab = readlocal(class_tab);//init the classified tab of classes
                if (class_tab == NULL)run =0 ;//type error handled in the function readlocal()
                else bool_local = 0;
            }
            local_menu(class_tab);
            break;

        case 'P'://print list not done yet
            list_menu(affect_tab);
            break;

        case 'E':// random part not done yet
            clear();
            emp_tab = place_list(emp_tab, class_tab);//not optimized for >1 run 
            if(_msize(stu_tab)/sizeof(student) > _msize(emp_tab)/sizeof(emplacement)){
                printf("error not enough emplacemets for student please add more places ");
                getch();
                break;
            }
            affect_tab = init_affect(affect_tab,stu_tab);
            //printemp(emp_tab);
            randomlocal(emp_tab, affect_tab);
            printaffect(affect_tab);
            emp_tab = (emplacement *)realloc(emp_tab, sizeof(emplacement));
            getch();
            break;

        default:
            printf("saisie invalide");
            getch();
            break;
        }
    }

    // free all the tables
    affect_tab = kill(affect_tab); 
    stu_tab = kill(stu_tab);
    class_tab = kill(class_tab);
    emp_tab = kill(emp_tab);

    return 0;
}