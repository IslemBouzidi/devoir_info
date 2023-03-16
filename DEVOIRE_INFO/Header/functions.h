#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "classes.h" 
#include "graphics.h"

// declaration of functions
classe *readlocal(classe *t);
classe *append_class(classe *t);
student *readeleve(student *);
student *append_stud(student *);
unsigned char ask(unsigned char);
void local_menu(classe *tab);
int modif(classe *ct,classe t, unsigned short id0 ,unsigned char name0[], unsigned int nmax0, unsigned char used0);
int checkid(classe *ct ,unsigned short n);

#endif