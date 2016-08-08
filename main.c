#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

time_t t;

typedef struct p{

char estado[1];
char tipo[1];
char fit[2];
int inicio;
int tam;
char nombre[16];
}particion;


typedef struct e{
char estado[1];
char fit[2];
int inicio;
int tam;
int proximoEbr;
char nombre[16];
}ebr;

typedef struct archivo{
int mbr_tam;
char tiempo[100];
int numDisco;
particion p1;
particion p2;
particion p3;
particion p4;
}MBR;


void llamada(){
char var;
printf("Ingrese el comando indicado \n");
char cadena[200];
fgets(cadena,200,stdin);
//printf("%s",cadena);

char * pch;
  pch = strtok (cadena," ,.-");
  while (pch != NULL)
  {

  if(strcmp(pch,"mkdisk")){
    break;
  }else{
   printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  }
}




int main()
{

    llamada();

    return 0;
}
