#ifndef CLASSES_H
#define CLASSES_H
 
// declaration of classe 
typedef struct classe{
    unsigned int id;
    unsigned char name[16];
    unsigned int nmax;
    unsigned char used;
} classe;

typedef struct student{
    unsigned char name[16];
    unsigned char surname[32];
    unsigned short groupe;
} student;

typedef struct affectation{
    unsigned char name[16];
    unsigned char surname[32];
    unsigned short groupe;
    unsigned char nlocal[16];
    unsigned int emp;
} affectation;

typedef struct emplacement{
    unsigned char nlocal[16];
    unsigned int emp;
    unsigned int count;
} emplacement;


#endif