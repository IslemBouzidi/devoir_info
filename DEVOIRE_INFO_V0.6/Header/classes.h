#ifndef CLASSES_H
#define CLASSES_H
 

typedef struct{//structure of a local placed in "locaux.txt"
    unsigned int id;
    unsigned char name[16];
    unsigned int nmax;
    unsigned char used;
} classe;

typedef struct{//structure of a student placed in "eleves.txt"
    unsigned char name[16];
    unsigned char surname[32];
    unsigned short groupe;
} student;

typedef struct{//structure of a combination between classe and student
    unsigned char name[16];
    unsigned char surname[32];
    unsigned short groupe;
    unsigned char nlocal[16];
    unsigned int emp;
} affectation;

typedef struct{//a helpin/temporary structure created to helping us for randomizing places
    unsigned char nlocal[16];
    unsigned int emp;
    unsigned int count;
} emplacement;


#endif