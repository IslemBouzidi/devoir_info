#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "..\Header\classes.h"
#include "..\Header\functions.h"
#include "..\Header\graphics.h"

void printstruct(classe *strct){//afficher la tableau des classe
    int i = 0, size;
    size = _msize(strct) / sizeof(classe);
    for(i = 0; i < size; i++ )printf("identifiant :%-10d\tnom :%-10s\tnombre de places :%-10d\tutilise :%-10d\n",strct[i].id,strct[i].name, strct[i].nmax, strct[i].used );
    return ;
}

void printaffect( affectation *affect){//afficher la tableau des emplacement 
    int j=0, size;
    size = _msize(affect) / sizeof(affectation);
    for(j= 0; j < size; j++ )printf("Nom :%-20s\tPrenom :%-20s\tGroupe :%-5d\tLocal :%-5s\tEmplacement :%-5d\n",affect[j].name,affect[j].surname,affect[j].groupe,affect[j].nlocal, affect[j].emp);
     
}
void main_print(){
    printf("Veuillez appuyer sur la lettre entre crochet pour executer la tache:\n1. Gestion des [L]ocaux\n2. Affectation des [E]mplacements\n3. [P]roduction des listes\n4. [S]ortie\n");

}
void local_print(){
    printf("Veuillez appuyer sur la lettre entre crochet pour executer la tache :\n1. [L]ister les locaux\n2. [A]jouter un local\n3. [M]odifier un local\n4. [S]upprimer un local\n5. [R]etour au menu principal\n\n");

}
void list_print(){
    printf("Veuillez appuyer sur la lettre entre crochet pour executer la tache :\n1. Construction de la liste [G]lobale\n2. Construction des listes [L]ocales\n3. [R]etour au menu principal\n\n");
}
void print_local_lists( classe *a){
    char file_name[16], line[100],i=0;
    for(int i=0;i< _msize(a)/sizeof(classe);i++)
    {
        
        strcpy(file_name, a[i].name);
        printf("\n%s\n",file_name);
        strcat(file_name,".txt");

        FILE* file = fopen(file_name,"r");
        if (file) {
            while (fgets(line, 100, file)) {
                printf("%s", line);
            }
            fclose(file);
            }
        else printf("%s local is not used yet",a[i].name);
    }
    }

void clear(){
    system("@cls||clear");//clean prompt
}
