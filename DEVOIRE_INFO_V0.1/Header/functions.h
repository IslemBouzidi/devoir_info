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
int modif(classe *ct,int index, unsigned short id0 ,unsigned char name0[], unsigned int nmax0, unsigned char used0);
int checkid(classe *ct ,unsigned short n);
affectation *init_affect(affectation *a, student *b);
void randomlocal(emplacement *a, affectation *b);
emplacement *place_list(emplacement *tab,classe *a);

#endif