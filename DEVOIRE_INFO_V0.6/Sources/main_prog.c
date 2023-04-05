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
    unsigned char task,run = 1, bool_local = 1, bool_stu = 1;
    float pct = 100;

    // creation of one element's table
    class_tab = (classe *)calloc(1, sizeof(classe)); 
    stu_tab = (student *)calloc(1, sizeof(student));
    emp_tab =(emplacement *)calloc(1 , sizeof(emplacement));

    // error raising
    if (class_tab == NULL || stu_tab == NULL || emp_tab == NULL){
        printf("\ninsufisent storage");
        exit(1);
    }
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
                if (stu_tab == NULL)run =0 ;//type error handled in the function readlocal()
                else bool_local = 0;
            }
            local_menu(class_tab);
            break;

        case 'P':
            list_menu(affect_tab, class_tab);
            break;

        case 'E':
            if (bool_stu){
                stu_tab = readeleve(stu_tab);//init the classified tab of students
                if (stu_tab == NULL)run =0 ;//type error handled in the function readlocal()
                else bool_stu = 0;
            }
            if (bool_local){
                class_tab = readlocal(class_tab);//init the classified tab of classes
                if (stu_tab == NULL)run =0 ;//type error handled in the function readlocal()
                else bool_local = 0;
            }
            clear();

            if (affect_tab != NULL)kill(affect_tab);//checking if affect tab were filled before 
            affect_tab = (affectation *)calloc(1, sizeof(affectation));//init affect_tab

            // error raising
            if (affect_tab == NULL){
                printf("\ninsufisent storage");
                exit(1);
            }

            pct = ask_f("entrez le poucentage(de 0 jusqu'a 100) du nombre de places disponible que ne doit pas depasser chaque locale");
            emp_tab = place_list(emp_tab, class_tab, pct);//the choice of classes is handled in place_list()
            if(emp_tab == NULL){
                emp_tab =(emplacement *)calloc(1 , sizeof(emplacement));//init emp_tab at one element for further use
                break;
            }
            if(emp_error(emp_tab,stu_tab)){
                printf("\nerror not enough emplacemets for student please add more places ");
                getch();
                break;
            }
            affect_tab = init_affect(affect_tab,stu_tab);
            randomlocal(emp_tab, affect_tab);
            printaffect(affect_tab);
            affectation_list(affect_tab);
            emp_tab = (emplacement *)realloc(emp_tab, sizeof(emplacement));// reallocate one element (init)

            printf("\npress enter to return to the local menu");
            while (getch() != 13)continue;
            break;

        default:
            printf("\nsaisie invalide");
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