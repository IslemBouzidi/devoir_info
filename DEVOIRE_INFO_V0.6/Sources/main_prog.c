#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include "..\Header\classes.h"
#include "..\Header\functions.h"
#include "..\Header\graphics.h"


// main fonction
int main(void){
    // declarations/creation of one element table
    classe *class_tab = (classe *)calloc(1, sizeof(classe));
    student *stu_tab = (student *)calloc(1, sizeof(student));
    affectation *affect_tab = NULL;
    emplacement *emp_tab = (emplacement *)calloc(1 , sizeof(emplacement));
    unsigned char task = 0, run = 1, bool_local = 1, bool_stu = 1;
    float pct = 100;

    if (class_tab == NULL || stu_tab == NULL || emp_tab == NULL){//error raising
        printf("\ninsufisent storage");
        exit(1);
    }

    //infinite loop /main menu
    while(run){
        clear();//cleaning the prompt
        main_print();//main menu print
        task = ask("task");

        switch (task){
        case 'S': //sortie
            run = 0;
            break;

        case 'L': //local
            if (bool_local){//reading "local.txt" for the first time
                class_tab = readlocal(class_tab);//init the classified tab of classes
                if (stu_tab == NULL)run =0 ;//error raising for more details check readlocal()
                else bool_local = 0;
            }
            local_menu(class_tab);//recursive function
            break;

        case 'P':
            list_menu(affect_tab, class_tab);//recursive function
            break;

        case 'E':
            if (bool_stu){//reading "eleve.txt" for the first time
                stu_tab = readeleve(stu_tab);//init the classified tab of students
                if (stu_tab == NULL)run =0 ;//error raising for more details check readeleve()
                else bool_stu = 0;
            }
            if (bool_local){//reading "local.txt" for the first time
                class_tab = readlocal(class_tab);//init the classified tab of classes
                if (stu_tab == NULL)run =0 ;//error raising for more details check readlocal()
                else bool_local = 0;
            }

            clear();//clean the prompt
            if (affect_tab != NULL)kill(affect_tab);//checking if affect tab were filled before 
            affect_tab = (affectation *)calloc(1, sizeof(affectation));//init affect_tab by allocating one element

            if (affect_tab == NULL){// error raising
                printf("\ninsufisent storage");
                printf("\npress enter to return to the main menu");
                while (getch() != 13)continue;
                break;
            }

            pct = ask_f("enter a percentage(range :0 to 100) of available places that each classe must not exceed");
            emp_tab = place_list(emp_tab, class_tab, pct);//filling an table of all available place check place_list()
            if(emp_tab == NULL){//error raising
                emp_tab =(emplacement *)calloc(1 , sizeof(emplacement));//init emp_tab at one element for further use
                printf("\ninsufisent storage");
                printf("\npress enter to return to the main menu");
                while (getch() != 13)continue;
                break;
            }
            if(emp_error(emp_tab,stu_tab)){//check if we have enough places for student
                printf("\nerror not enough emplacemets for student please add more places ");
                printf("\npress enter to return to the main menu");
                while (getch() != 13)continue;
                break;
            }
            affect_tab = init_affect(affect_tab,stu_tab);//init affect_tab(name, surname, groupe) check init_affect()
            randomlocal(emp_tab, affect_tab);//randomize places 
            printaffect(affect_tab);//printing affect_tab
            affectation_list(affect_tab);//writing "affectation.txt"
            
            printf("\npress enter to return to the local menu");
            while (getch() != 13)continue;
            break;

        default:
            printf("\nsaisie invalide");
            printf("\npress enter to return to the local menu");
            while (getch() != 13)continue;
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