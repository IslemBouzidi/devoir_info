#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include "..\Header\classes.h"
#include "..\Header\functions.h"
#include "..\Header\graphics.h"


//locaux 
classe *readlocal(classe *t){
    /*
       this functions takes the classe's table pointer (classe *) which is stored in the data
       open\read the file "locaux.txt"
       extract and classify data from the file by parsing char by char
       this function uses atoi which is a stdlib's function which convert str to int
       reallocate dynamically as needed
       close the file
       return the pointer of the classified ,filled classe table (classe *)
    */
    unsigned char class_index = 0, lettre = 0,type_index = 0, word[32], j = 0;
    FILE *fic =fopen("locaux.txt", "r");// opening file
    if (fic == NULL){//unfound file error raising
        printf("unfound file Error, please put the file \"locaux.txt\" in the folder\n");
        fclose(fic);
        return NULL;
    }
    do{ // reading the file char by char
        lettre = fgetc(fic);
        if(lettre == 9 || lettre == 10 || lettre == 255){// gestion of tabulation and back to the line or end of file
            word[j] = 0; //end of read word
            switch (type_index){
            case 0://id
                if(class_index){// add an element in class_tab if it isn't the first data line classe_tab contains already one element
                t = append_class(t);
                if(t == NULL){//lack of storage error raising
                    printf("insufisent storage error, may the file contains too much data\n");
                    fclose(fic);
                    return NULL;}
                }
                t[class_index].id = atoi(word); 
                break;
            case 1://name
                strcpy(t[class_index].name, word);
                break;
            case 2://place number
                t[class_index].nmax = atoi(word);
                break;
            case 3://usable
                t[class_index].used = atoi(word);
                class_index++;//may the file contains one other line of data
                break;
            default:
                break;
            }
            j = 0;//init index of word
            type_index = (type_index+1) % 4;
        }
        else{
            word[j] = lettre;//store the word char by char
            j++;
        }
    }while(lettre != 255);//end of file
    fclose(fic);
    return t;
}


classe *append_class(classe *t){
    /* this function take a type :"classe" table pointer (classe *) and add one classe(storage) to the table
     return pointer to the new table (classe *)  */
    size_t size;
    size = _msize(t) + sizeof(classe);
    t = (classe *)realloc(t, size);
    //t[_msize(t)/sizeof(classe)-1].id = 0; //init on 0 private id 
    return t;
}


void local_menu(classe *tab){
    unsigned char task = 0, name0[20], used0 = 0;
    unsigned short id = 0, idm = 0;
    unsigned int nm;
    clear();
    local_print();
    task = ask(task);
    switch (task){
        case 'R'://return to the main menu
            break;

    case 'L':
        printstruct(tab);
        printf("press enter to return to the local menu \n");
        while (getch() != 13)continue;
        local_menu(tab);
        break;

    case 'A':
        printf("");
        break;

    case 'S':
        break;

    case 'M':
        clear();
        printf("enter the id of the local you want to modify :");
        scanf("%d", &id);//note for future we should raise an error if not available
       // if(checkid(tab,id) == -1) break;
        printf("\n\nchange the id[y/n]");

        fflush(stdin);
        task = getchar();

        if(task =='y'){
            printf("\nid :");
            scanf("%d",&idm);
        }
        else if (task == 'n')idm = tab[id].id;
        else break;

        printf("\n\nchange the name[y/n]");
        fflush(stdin);
        task = getchar();

        if(task =='y'){
            printf("\nname :");
            gets(name0);
        
        }
        else if (task == 'n')strcpy(name0 ,tab[id].name);
        else break;

        printf("\n\nchange the number of classe[y/n]");
        task = getchar();
        getchar();

        if(task =='y'){
            printf("\nnumber of classe :");
            scanf("%d", &nm);
        }
        else if (task == 'n')nm = tab[id].nmax;
        else break;

        printf("\n\nchange the classe's state[y/n]");
        task = getchar();
        getchar();

        if(task =='y'){
            printf("\nused[y/n]:");
            task = getchar();
            if(task =='y')used0 = 1;
            else if (task == 'n')used0 = 2;
            else break;
            }
        else if (task == 'n')nm = idm = tab[id].nmax;
        else break;
        if (modif(tab, tab[id],idm, name0, nm, used0))
        break;
    default:
            break;


    }
}

int modif(classe *ct,classe t, unsigned short id0 ,unsigned char name0[], unsigned int nmax0, unsigned char used0){
    if ((id0 != 0)&&(checkid(ct,id0) != -1)&&(id0 != t.id))t.id = id0;
    else{
        printf("error :id invalide try agin you loose little pogger");
        return 1;
    }
    if(nmax0 != t.nmax)t.nmax = nmax0;
    if (used0 != t.used)t.used = used0;
    if (strlen(name0) < sizeof(t.name) && !strcmp(t.name , name0))strcpy(t.name , name0);
    else{
        printf("error : too long name, try again little brat ");
        return 1;
    }

    return 0;
}

int checkid(classe *ct ,unsigned short n){
    /* check id retourne l'index de la classe d'id n si elle exite sinon retourn -1 valeur  impossible d'id*/
    int i;
    for(i = 0; i < _msize(ct)/sizeof(classe); i++){
        if (ct[i].id == n)return i;
    }
    return -1;
}

//student part


student *readeleve(student *t){
    /*
       this functions takes the classe's table pointer (classe *) which is stored in the data
       open\read the file "locaux.txt"
       extract and classify data from the file by parsing char by char
       this function uses atoi which is a stdlib's function which convert str to int
       reallocate dynamically as needed
       close the file
       return the pointer of the classified ,filled classe table (classe *)
    */
    unsigned char stu_index = 0, lettre = 0,type_index = 0, word[32], j = 0;
    FILE *fic =fopen("eleves.txt", "r");// opening file
    if (fic == NULL){//unfound file error raising
        printf("unfound file Error, please put the file \"eleves.txt\" in the folder\n");
        fclose(fic);
        return NULL;
    }
    do{ // reading the file char by char
        lettre = fgetc(fic);
        if(lettre == 9 || lettre == 10 || lettre == 255){// gestion of tabulation and back to the line or end of file
            word[j] = 0; //end of red word
            switch (type_index){
            case 0://name
                if(stu_index){// add an element in class_tab if it isn't the first data line classe_tab contains already one element
                t = append_stud(t);
                if(t == NULL){//lack of storage error raising
                    printf("insufisent storage error, may the file contains too much data\n");
                    fclose(fic);
                    return NULL;}
                }
                strcpy(t[stu_index].name ,word); 
                break;
            case 1://surname
                strcpy(t[stu_index].surname, word);
                break;
            case 2://group
                t[stu_index].groupe = atoi(word);
                stu_index++;
                break;
            default:
                break;
            }
            j = 0;//init index of word
            type_index = (type_index+1) % 3;
        }
        else{
            word[j] = lettre;//store the word char by char
            j++;
        }
    }while(lettre != 255);//end of file
    fclose(fic);
    return t;
}


student *append_stud(student *t){
    /* this function take a type :"student" table pointer (student *) and add one student(storage) to the table
     return pointer to the new table (student *)  */
    size_t size;
    size = _msize(t) + sizeof(student);
    return (student *)realloc(t, size);
}

 
//other
unsigned char ask(unsigned char request[]){
    /* this fontcion is called to read one char input on the keyboard and empty the buffer by fflush()
    in stdlib library and take one string argument "the request"*/
    unsigned char task;
    if(request == NULL)continue;
    else printf("%s :", request);
    task = getchar();
    fflush(stdin);//our hero nhabek hbibi
    return task;    
}

unsigned char* ask_s(unsigned short range ,unsigned char request[]){
    /* this fontcion is called to read one string input of (range -1) maximum range on the keyboard and 
    empty the buffer by fflush() in stdlib library and take one string argument "the request"*/
    unsigned char task[range];
    if(request == NULL)continue;
    else printf("%s :", request);
    task = gets(stdin);
    fflush(stdin);//our hero nhabek hbibi
    return task;    
}