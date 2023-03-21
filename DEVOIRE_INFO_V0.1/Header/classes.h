#ifndef CLASSES_H
#define CLASSES_H
 
// declaration of classe 
typedef struct{
    unsigned short id;
    unsigned char name[16];
    unsigned int nmax;
    unsigned char used;
} classe;








typedef struct{
    unsigned char name[16];
    unsigned char surname[32];
    unsigned short groupe;
} student;

typedef struct{
    unsigned char name[16];
    unsigned char surname[32];
    unsigned short groupe;
    unsigned char nlocal[16];
    unsigned int emp;
} affectation;

typedef struct{
    unsigned char nlocal[16];
    unsigned int emp;
} emplacement;


#endif