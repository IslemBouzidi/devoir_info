#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>
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
    unsigned short class_index = 0;
    unsigned char lettre = 0,type_index = 0, word[32], j = 0;

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
    return t;
}


void local_menu(classe *tab){
    //declaration
    unsigned char task = 0, name0[20], used0 = 0;
    int nm, id1 = 0, idm = 0;
    

    //menu
    clear();
    local_print();
    task = ask("task");

    switch (task){

    case 'R'://return to the main menu
            break;

    case 'L'://listing the locals done

        printstruct(tab);
        printf("\npress enter to return to the local menu");
        while (getch() != 13)continue;
        local_menu(tab);
        break;

    case 'A':// Adding local
        clear();
        tab = append_class(tab);
        if(tab == NULL){
            printf("\nerror : not enough storage");
            printf("\npress enter to return to the local menu");
            while (getch() != 13)continue;
            local_menu(tab);
            break;
        }

        printf("veuillez entrer les caracteristique de la nouvelle classe :");
        id1 = _msize(tab)/sizeof(classe) -1;
        printf("%d", id1);
        idm = ask_d("\nid");

        if(checkid(tab,idm) != -1){
            printf("\nerror : id alreadu used try again");
            printf("\npress enter to return to the local menu");
            while (getch() != 13)continue;
            local_menu(tab);
            break;
        }

        ask_s(name0, "\nname");
        nm = ask_d("\nnumber of places");
        task = ask("\nused[y/n]");
            if(task =='y')used0 = 1;
            else if (task == 'n')used0 = 0;
            else break;

        if (!modif(tab,id1,idm, name0, nm, used0))printstruct(tab);
        ask_to_save(tab);
        printf("press enter to return to the local menu");
        while (getch() != 13)continue;
        local_menu(tab);
        break;

    case 'S': // deleting local
        clear();
        id1 = ask_d("enter the id of the local you want to delete");
        id1 = checkid(tab,id1);
        if(id1 == -1){
            printf("\nerror : invalid id try again");
            printf("\npress enter to return to the local menu");
            while (getch() != 13)continue;
            local_menu(tab);
            break;
        }
        tab = delete(tab, id1);
        ask_to_save(tab);
        printf("\npress enter to return to the local menu");
        while (getch() != 13)continue;
        local_menu(tab);
        break;

    case 'M': // nodify a local
        clear();
        id1 = ask_d("enter the id of the local you want to modify");
        id1 = checkid(tab,id1);
        if(id1 == -1){
            printf("\nerror : invalid id try again");
            printf("press enter to return to the local menu \n");
            while (getch() != 13)continue;
            local_menu(tab);
            break;
        }

        task = ask("change the id[y/n]");
        if(task =='y')idm = ask_d("\nid");
        else if (task == 'n')idm = tab[id1].id;
        else break;

        task = ask("\n\nchange the name[y/n]");
        if(task =='y')ask_s(name0, "\nname");
        else if (task == 'n')strcpy(name0 ,tab[id1].name);
        else break;

        task = ask("\n\nchange the number of places[y/n]");
        if(task =='y')nm = ask_d("\nnumber of places");

        else if (task == 'n')nm = tab[id1].nmax;
        else break;

        task = ask("\n\nchange the classe's state[y/n]");
        if(task =='y'){
            task = ask("\nused[y/n]");
            if(task =='y')used0 = 1;
            else if (task == 'n')used0 = 0;
            else break;
            }
        else if (task == 'n')used0= tab[id1].used;
        else break;

        if (!modif(tab,id1,idm, name0, nm, used0)){
            printstruct(tab);
            ask_to_save(tab);
        }
        printf("\npress enter to return to the local menu");
        while (getch() != 13)continue;
        local_menu(tab);
        break;

    default:
        local_menu(tab);
        break;
    }
}

int modif(classe *ct,int index, int id0 ,unsigned char name0[], int nmax0, unsigned char used0){
    if (id0 < 0 ){
        printf("\nerror :id invalide try again");
        return 1;
    }
    else if(id0 != ct[index].id)ct[index].id = id0;

    if(nmax0 < 0){
        printf("\nerror :number of places can't be negatif ");
    }
    else if(nmax0 != ct[index].nmax)ct[index].nmax = nmax0;

    if (used0 != ct[index].used)ct[index].used = used0;

    if (strlen(name0) < sizeof(ct[index].name) && name0 != NULL )strcpy(ct[index].name , name0);
    else if(strcmp(ct[index].name , name0))return 0;
    else{
        printf("\nerror : too long name, try again little brat ");
        return 1;
    }
    return 0;
}

int checkid(classe *ct ,unsigned int n){
    /* check id retourne l'index de la classe d'id n si elle exite sinon retourn -1 valeur  impossible d'id*/
    int i;
    for(i = 0; i < _msize(ct)/sizeof(classe); i++){
        if (ct[i].id == n)return i;
    }
    return -1;
}

classe *delete(classe *tab, unsigned int index){
    permute(tab, index, _msize(tab)/sizeof(classe)-1);
    tab = (classe *)realloc(tab, _msize(tab) - sizeof(classe));
    return tab;
}

void permute(classe *tab,unsigned int index1,unsigned int index2){
    classe c1 = tab[index1];
    if(index1 == index2)return ;
    /*
    if ((_msize(tab)/sizeof(classe) < index1)||(_msize(tab)/sizeof(classe) < index1)){
        printf("error index out of range");
        return ;
    }*/ //inutile etant donne qu'on verifie si l'index est valable avant d'entrer dans delete()
    modif(tab,index1,tab[index2].id,tab[index2].name, tab[index2].nmax, tab[index2].used);
    modif(tab,index2,c1.id,c1.name, c1.nmax, c1.used);
    return ;
}

void savelocal(classe *tab){
    FILE *fic = fopen("locaux.txt","w");
    int i;
    if (fic == NULL){
        printf("error : oppening \"locaux.txt\" is impossible");
        return;
    }
    for(i = 0; i < _msize(tab)/sizeof(classe); i++ )fprintf(fic, "%d\t%s\t%d\t%d\n",tab[i].id, tab[i].name,tab[i].nmax,tab[i].used);
    fclose(fic);
    return;
}

void ask_to_save(classe *tab){
    char task;
    task = ask("\nsave the changes[y/n]");
    if(task =='y')savelocal(tab);
    else if (task == 'n')return;
    else ask_to_save(tab);
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
    unsigned short stu_index = 0;
    unsigned char lettre = 0,type_index = 0, word[32], j = 0;
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

//affectation part
void list_menu(affectation *affect, classe *a)
{
    unsigned char task=0;

    clear();
    list_print();

    task = ask("task");

    switch(task)
    {
        case 'G':// Constraction de la list globale
            qsort(affect,_msize(affect)/sizeof(affectation),sizeof(affectation),compare); // sorting affact tab in a alphabatic ordre 
            printaffect(affect); // printing the results
            list_global(affect); // saving the results in a txt file
            printf("\npress enter to return to the local menu"); // return to list menu
            while (getch() != 13)continue;
            list_menu(affect,a);
            break;

        case 'L':// Constraction des lists locals 

            qsort(affect,_msize(affect)/sizeof(affectation),sizeof(affectation),cmp_name); // grouping the data by local and sorting it by order of emplacement 
            production_local(affect,a);// saving the results in txt files
            print_local_lists(a); // printing the lists
            printf("\npress enter to return to the local menu");// return to list menu
            while (getch() != 13)continue;
            list_menu(affect,a); 
            break;

        case 'R'://return  
            break;
            
        default :
            break;
    }
    return;
}
    
// affectation is a new data type, we fill the name and surname columns with the data in student class
affectation *init_affect(affectation *a, student *b){
    size_t size;
    int i;
    size = _msize(b)*sizeof(affectation)/sizeof(student);
    a = (affectation *)realloc(a, size);
    for(i =0 ; i< (size/sizeof(affectation)) ; i++){
        strcpy(a[i].name,b[i].name);
        strcpy(a[i].surname,b[i].surname);
        a[i].groupe = b[i].groupe;
    }
    return a;
}

emplacement *place_list(emplacement *tab , classe *a, float pourcentage){ //tab have to be freed in an another function , used =0 is handled in this part
    /* les pourcentage sont arrondis toujours a la valeur superieur en utilisant ceil
        la liste tab est deja randomisé*/
    unsigned char task;
    size_t size =_msize(a)/sizeof(classe);
    int i, k =0, n; 
    unsigned int index;
    for(i = 0 ; i < size; i++){
        if(!a[i].used){
            printf("\nid of classe :%d ",a[i].id);
            task = ask("should I take this classe in consideration[y/n]");
            if( task =='y'){
                n = ceil(a[i].nmax*pourcentage/100);
                tab = (emplacement *)realloc(tab, _msize(tab) + sizeof(emplacement));
                if(tab == NULL){
                    printf("\nerror :not enough storage");
                    printf("\npress enter to return to the main menu");
                    while (getch() != 13)continue;
                    return NULL;
                }
                strcpy(tab[k].nlocal , a[i].name);
                tab[k].emp = n;
                tab[k].count = 1; //init the count at one for randomlocal()
                k++;
            }
            else if (task == 'n')continue;
            else {
                printf("\nincorrect answer please try again");
                return NULL;
            }
        }
    }
    tab = (emplacement *)realloc( tab,_msize(tab)-sizeof(emplacement)); //raise error if NULL
    if(tab == NULL){
        printf("\nerror :not enough storage");
        printf("\npress enter to return to the main menu");
        while (getch() != 13)continue;
        return NULL;
    }
    return tab ;
}

char emp_error(emplacement *t1, student *t2){
    int j, sum = 0;
    for(j = 0; j < _msize(t1)/sizeof(emplacement) ; j++)sum += t1[j].emp;
    if (sum >= _msize(t2)/sizeof(student))return 0;//valid
    else return 1;//nope
}
void randomlocal(emplacement *a, affectation *b){
    int i, n =_msize(a)/sizeof(emplacement) , m= _msize(b)/sizeof(affectation), index ;
    srand(time(NULL));
    for(i = 0 ; i < m  ; i++){
        index = rand() % (n);  // if k is too big behind rand() we have to change rand()
        strcpy(b[i].nlocal, a[index].nlocal);
        b[i].emp = a[index].count;
        a[index].count++;
        if (a[index].emp == a[index].count){
            strcpy(a[index].nlocal, a[n-1].nlocal);
            a[index].emp = a[n-1].emp;
            n--;
        }
    }
}
// creating a txt file called affectations.txt and fill with the results of random locals fonction
int affectation_list(affectation *affect){
    FILE* fp_out = fopen("affectations.txt", "w");
    if (fp_out == NULL) {
        printf("Error: could not create file 'affglob.txt'\n");
        return 1;
    }
    for(int i=0; i<(_msize(affect)/sizeof(affectation));i++){
        fprintf(fp_out, "nom:%s\t prenom:%s\t groupe:%d\t local:%s\t emplacement:%d \n",affect[i].name, affect[i].surname,affect[i].groupe,affect[i].nlocal,affect[i].emp);    
    }
    printf("\n affectation.txt has been created successfully");
    fclose(fp_out);
    return 1;
}

// Production of lists part
// compare fonction will be used in qsort, to order students in a alphabatic order 
int compare(const void *x, const void *y){ 
    affectation *stud1= (affectation *)x;
    affectation *stud2= (affectation *)y;
    return strcmp(stud1->name, stud2->name); // we use -> because it's a pointer
}

// this fonction will sort affactation table according to local and the numbre of place
int cmp_name(const void *a, const void *b){
    int diff= strcmp(((affectation*)a)->nlocal, ((affectation*)b)->nlocal);
    if(diff)
        return -diff;
    return ((affectation*)a)->emp -((affectation*)b)->emp;
}
// this fonction will create affglob.txt
int list_global(affectation *affect){
    FILE* fp_out = fopen("affglob.txt", "w");
    if (fp_out == NULL) {
        printf("Error: could not create file 'affglob.txt'\n");
        return 1;
    }
    for(int i=0; i<(_msize(affect)/sizeof(affectation));i++){
        fprintf(fp_out, "nom:%s\t prenom:%s\t groupe:%d\t local:%s\t emplacement:%d \n",affect[i].name, affect[i].surname,affect[i].groupe,affect[i].nlocal,affect[i].emp);    
    }
    printf("\n affglob.txt has been created successfully");
    fclose(fp_out);
    return 1;
}
// this fonction will create AffNomDuLocal.txt files
int production_local(affectation *affect, classe *a){
    int j=0,k=0;
    char file_name[16];
    for(int i=0;i< _msize(a)/sizeof(classe);i++)
    {
        strcpy(file_name,affect[k].nlocal);
        strcat(file_name,".txt");

        FILE* fp_out = fopen(file_name,"w");
        if (fp_out == NULL) {
        printf("Error: could not create file '%s'\n",file_name);
        return 1;
            }
        while(strcmp(affect[j].nlocal, affect[k].nlocal)==0)
        {

            fprintf(fp_out, "emplacement:%d\tnom:%s\t prenom:%s\t groupe:%d\t \n",affect[j].emp,affect[j].name, affect[j].surname,affect[j].groupe);
            j++;
        }
        k= j;
        i++;
        fclose(fp_out);
    }
    printf("\n local lists have been created successfully\n");
    return 1;
}

//other
unsigned char ask(unsigned char request[]){
    /* this fontcion is called to read one char input on the keyboard and empty the buffer by fflush()
    in stdlib library and take one string argument "the request"*/
    unsigned char task;
    if(request != NULL) printf("%s :", request);
    task = getchar();
    fflush(stdin);//our hero nhabek hbibi
    return task;    
}

unsigned char* ask_s(unsigned char *task ,unsigned char request[]){
    /* this fontcion scanf on the keybord a string and place it on the adress task and also empty the buffer*/
    unsigned char i= 0;
    if(request != NULL) printf("%s :", request);
    fgets(task,20,stdin);
    for(i; i<20; i++){
        if(task[i] == 10)task[i] = 0;// to fix a bug:fgets read also the back to line char
    }
    fflush(stdin);//our hero nhabek hbibi
    return task;    
}
unsigned int ask_d(unsigned char request[]){
    /* this fontcion is called to read one char input on the keyboard and empty the buffer by fflush()
    in stdlib library and take one string argument "the request"*/
    unsigned int i;
    if(request != NULL) printf("%s :", request);
    scanf("%d",&i);
    fflush(stdin);//our hero nhabek hbibi
    return i;
}

unsigned int ask_f(unsigned char request[]){
    /* this fontcion is called to read one char input on the keyboard and empty the buffer by fflush()
    in stdlib library and take one string argument "the request"*/
    float i;
    if(request != NULL) printf("%s :", request);
    scanf("%f",&i);
    fflush(stdin);//our hero nhabek hbibi
    return i;
}

void *kill(void *tab){
    //free any type of array
    free(tab);
    tab = NULL;
    return tab;
}
