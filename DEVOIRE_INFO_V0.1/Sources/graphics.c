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
    for(i = 0; i < size; i++ )printf("identifiant :%d\tnom :%s\tnombre de places :%d\tutilise :%d\n",strct[i].id,strct[i].name, strct[i].nmax, strct[i].used );
    return ;
}
void printstruct2(student strct){
    printf("name :%s\nsurname :%s\ngroupe:%d\n",strct.name,strct.surname, strct.groupe);
}


void printaffect( affectation *affect){//afficher la tableau des classe
    int j, size;
    size = _msize(affect) / sizeof(affectation);
    for(j = 0; j < size; j++ )printf("Nom :%s\tPrenom :%s\tGroupe :%d\tLocal :%s\tEmplacement :%d\n",affect[j].name,affect[j].surname,affect[j].groupe,affect[j].nlocal, affect[j].emp);
    return ;
}

void printemp( emplacement *e){//afficher la tableau des classe
    int j, size;
    size = _msize(e) / sizeof(emplacement);
    for(j = 0; j < size; j++ )printf("Nom :%s\tEmplacement :%d\n",e[j].nlocal,e[j].emp);
    return ;
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
void clear(){
    system("@cls||clear");//clean prompt
}
//\tLocal :%s\tEmplacement :%d