#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


char* substr(char* cadena, int comienzo, int longitud){
	if (longitud == 0) longitud = strlen(cadena)-comienzo-1;

	char *nuevo = (char*)malloc(sizeof(char) * longitud);

	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

void llamada(){
printf("Ingrese el comando indicado \n");
int i=0;
int bandera=0;
char cadena[200];
char separador[]=" ";
char path[200]="";
fgets(cadena,200,stdin);
char *t=NULL;
t= strtok(cadena,separador);
while(t!=NULL){

int longitud= strlen(t);
if(bandera==1){
strcat(path," ");
strcat(path,t);

if(strcasecmp(substr(t,longitud-1,1),"\n")==0){

if(strcasecmp(substr(t,longitud-2,1),"\"")==0){
nodoc *nuevo= CrearComando(path);
nodocomando=InsertarComando(nodocomando,nuevo);
bandera=0;
}else{
bandera=1;
strcpy(path,t);
}
}else{
if(strcasecmp(substr(t,longitud-1,1),"\"")==0){
nodoc *nuevo= CrearComando(path);
nodocomando=InsertarComando(nodocomando,nuevo);
bandera=0;
}else{
bandera=1;
}

}
}

if(strcasecmp(substr(t,7,1),"\"")==0){

if(strcasecmp(substr(t,longitud-1,1),"\n")==0){


if(strcasecmp(substr(t,longitud-2,1),"\"")==0){
nodoc *nuevo= CrearComando(t);
nodocomando=InsertarComando(nodocomando,nuevo);
bandera=0;
}else{
bandera=1;
strcpy(path,t);
}

}else{


if(strcasecmp(substr(t,longitud-1,1),"\"")==0){
nodoc *nuevo= CrearComando(t);
nodocomando=InsertarComando(nodocomando,nuevo);
bandera=0;
}else{
bandera=1;
strcpy(path,t);
}

}


}else{
nodoc *nuevo= CrearComando(t);
nodocomando= InsertarComando(nodocomando,nuevo);
}

t = strtok( NULL, separador);
}
//ImprimirComandos(nodocomando);
nodoc *aux=nodocomando;
while(aux!=NULL){
if(strcasecmp(aux->comando,"mkdisk")==0){
printf("ES UN COMANDO PARA CREAR UN DISCO DURO \n");
DiscoDuro();
}
aux=aux->siguiente;
}

}

void CrearDiscoDuro(){
}


void DiscoDuro(){
FILE *f;
char escritor[1024]="\0";
char comparador[40];
char nombreArchivo[50];
char pathArchivo[80];
char tama[20];
char unidad[1];
nodoc *aux=nodocomando;
//PRIMER WHILE PARA EL TAMAÑO
while(aux!=NULL){
int td;
strncpy(comparador,aux->comando,7);
if(strcasecmp(comparador,"-size::")==0){
printf("YO DOY EL TAMAÑO y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(tama,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}
//WHILE PARA ENCONTRAR EL NOMBRE
aux=nodocomando;
while(aux!=NULL){
strncpy(comparador,aux->comando,7);
if(strcasecmp(comparador,"-name::")==0){
printf("\n YO DOY EL NOMBRE y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(nombreArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA ENCONTRAR LA PATH
aux=nodocomando;
while(aux!=NULL){
strncpy(comparador,aux->comando,7);
if(strcasecmp(comparador,"-path::")==0){
printf("\n YO DOY LA PATH Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(pathArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA ENCONTRAR LA UNIDAD
aux=nodocomando;
while(aux!=NULL){
strncpy(comparador,aux->comando,7);
if(strcasecmp(comparador,"+unit::")==0){
printf("\n YO DOY LA UNIDAD Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(unidad,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//QUITANDO LAS COMILLAS AL NOMBRE
int lnombre= strlen(nombreArchivo);
if(strcasecmp(substr(nombreArchivo,lnombre-1,1),"\n")==0){
strcpy(nombreArchivo,substr(nombreArchivo,1,lnombre-3));
}else{
strcpy(nombreArchivo,substr(nombreArchivo,1,lnombre-2));
}

f=fopen(nombreArchivo,"wb");
int c=0;
int tamArchivo;
tamArchivo=atoi(tama);

if(strcasecmp(unidad,"m\n")==0 || strcasecmp(unidad,"m")==0 || strcasecmp(unidad,"")==0){
for(c;c<1024*tamArchivo;c++){
fwrite(escritor,sizeof(escritor),1,f);
}
fclose (f);
}else if(strcasecmp(unidad,"k\n")==0 || strcasecmp(unidad,"k")==0){
for(c;c<tamArchivo;c++){
fwrite(escritor,sizeof(escritor),1,f);
}
fclose (f);
}
//printf("\n %d",td);
//printf("\n %s",nombreArchivo);
}



int main()
{
    nodocomando= IniciarListaComandos(nodocomando);
    llamada();

    return 0;
}
