#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "classes.h" 
#include "graphics.h"

// declaration of functions:
classe *readlocal(classe *t);
classe *append_class(classe *t);
student *readeleve(student *);
student *append_stud(student *);
unsigned char ask(unsigned char request[]);
unsigned char* ask_s(unsigned char * ,unsigned char request[]);
unsigned int ask_d(unsigned char request[]);
void local_menu(classe *tab);
int modif(classe *ct,int index, int id0 ,unsigned char name0[], int nmax0, unsigned char used0);
int checkid(classe *ct ,unsigned int n);
affectation *init_affect(affectation *a, student *b);
void randomlocal(emplacement *a, affectation *b);
emplacement *place_list(emplacement *tab,classe *a);
classe *delete(classe *tab, unsigned int index);
void permute(classe *tab,unsigned int index1,unsigned int index2);
void *kill(void *tab);  
void list_menu(affectation *affect, classe *a); 
//void list_local(affectation *affect);
int production_local(affectation *affect,classe *a);
int compare(const void *x, const void *y);
int cmp_name(const void* a, const void* b);
int list_global(affectation *affect);
void savelocal(classe *tab);
void ask_to_save(classe *tab);
#endif