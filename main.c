#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "comandos.h"

time_t t;
nodoc *nodocomando;

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
printf("Ingrese el comando indicado \n");
int i=0;
char cadena[200];
char separador[]=" ";
fgets(cadena,200,stdin);
char *t=NULL;
t= strtok(cadena,separador);
while(t!=NULL){
nodoc *nuevo= CrearComando(t);
nodocomando= InsertarComando(nodocomando,nuevo);
t = strtok( NULL, separador);
}
ImprimirComandos(nodocomando);
nodoc *aux=nodocomando;
while(aux!=NULL){
if(strcasecmp(aux->comando,"mkdisk")==0){
printf("ES UN COMANDO PARA CREAR UN DISCO DURO \n");
DiscoDuro();
}
aux=aux->siguiente;
}

}

char* substr(char* cadena, int comienzo, int longitud)
{
	if (longitud == 0) longitud = strlen(cadena)-comienzo-1;

	char *nuevo = (char*)malloc(sizeof(char) * longitud);

	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

void DiscoDuro(){
char comparador[40];
nodoc *aux=nodocomando;
while(aux!=NULL){
strncpy(comparador,aux->comando,7);
if(strcasecmp(comparador,"-size::")==0){
printf("YO DOY EL TAMAÑO y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
printf("\n %d",atoi(substr(aux->comando,7,sizeof(aux->comando))));
}
aux=aux->siguiente;
}
}



int main()
{
    nodocomando= IniciarListaComandos(nodocomando);
    llamada();

    return 0;
}
