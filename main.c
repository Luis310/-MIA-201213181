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


char* substr(char* cadena, int comienzo, int longitud){
	if (longitud == 0) longitud = strlen(cadena)-comienzo-1;

	char *nuevo = (char*)malloc(sizeof(char) * longitud);

	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

void llamada(){
//printf("Ingrese el comando indicado \n");
//fgets(cadena,200,stdin);
static const char script[]="comandos.txt";
FILE *lector=fopen(script,"r");
int i=0;
int bandera=0;
char cadena[200];
char separador[]=" ";
char path[200]="";
char *t=NULL;
if(lector!=NULL){
char recibido[300];
while(fgets(recibido,sizeof(recibido),lector)!=NULL){
printf("\n");
fputs(recibido,stdout);
printf("\n");
t= strtok(recibido,separador);
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
ImprimirComandos(nodocomando);
nodoc *aux=nodocomando;
while(aux!=NULL){
if(strcasecmp(aux->comando,"mkdisk")==0){
printf("ES UN COMANDO PARA CREAR UN DISCO DURO \n");
DiscoDuro();
}else if(strcasecmp(aux->comando,"rmdisk")==0){
printf("ES UN COMANDO PARA BORRAR UN DISCO DURO \n");
BorrarDiscoDuro();
}else if(strcasecmp(aux->comando,"fdisk")==0){
printf("ES UN COMANDO PARA AGREGAR PARTICION \n");
AdministrarDiscos();
}
aux=aux->siguiente;
}

nodocomando= IniciarListaComandos(nodocomando);

}
}





}

void AdministrarDiscos(){
FILE *f;
FILE *file;
char escritor[1000]="\0";
char tipo[10];
char comparador[40];
char nombreArchivo[50];
char fit[5];
char pathArchivo[80];
char tama[20];
char unidad[1];
char eliminar[10];
char add[10];
nodoc *aux=nodocomando;
//PRIMER WHILE PARA EL TAMAÑO
while(aux!=NULL){
int td;
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"size")==0){
printf("YO DOY EL TAMAÑO y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(tama,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA LA UNIDAD
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"unit")==0){
printf("\n YO DOY LA UNIDAD Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(unidad,substr(aux->comando,7,sizeof(aux->comando)));
}else{
strcpy(unidad,"");
}
aux=aux->siguiente;
}

//WHILE PARA EL PATH
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"path")==0){
printf("\n YO DOY LA PATH Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(pathArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA EL TIPO
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"type")==0){
printf("\n YO DOY EL TIPO Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(tipo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA EL FIT
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,3));
if(strcasecmp(comparador,"type")==0){
printf("\n YO DOY EL FIT Y ES: %s",substr(aux->comando,6,sizeof(aux->comando)));
strcpy(fit,substr(aux->comando,6,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA EL DELETE
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,6));
if(strcasecmp(comparador,"delete")==0){
printf("\n YO DOY EL DELETE Y ES: %s",substr(aux->comando,9,sizeof(aux->comando)));
strcpy(eliminar,substr(aux->comando,9,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA ENCONTRAR EL NOMBRE
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"name")==0){
printf("\n YO DOY EL NOMBRE y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(nombreArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA ENCONTRAR EL ADD
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,3));
if(strcasecmp(comparador,"add")==0){
printf("\n YO DOY EL NOMBRE y es : %s",substr(aux->comando,6,sizeof(aux->comando)));
strcpy(add,substr(aux->comando,6,sizeof(aux->comando)));
}
aux=aux->siguiente;
}
//CONVIRTIENDO EL TAMAÑO A INT
int tparticion;
tparticion=atoi(tama);

//QUITANDO LAS COMILLAS AL NOMBRE
char *sep1=NULL;
sep1= strtok(nombreArchivo,"\"");
strcpy(nombreArchivo,sep1);

//QUITANDO LAS COMILLAS AL PATH PARA HACER EL DIRECTORIO PRIMERO
char *separador=NULL;
separador= strtok(pathArchivo,"\"");
strcpy(pathArchivo,separador);


FILE *fr2= fopen(pathArchivo,"rb+");

if(fr2==NULL){
printf("\n NO SE PUEDE ACCEDER AL ARCHIVO");
}else{

int disponibles=0;
MBR mbr_aux;
fread(&mbr_aux,sizeof(MBR),1,fr2);
printf("\n El disco fue creado en la fecha: %s", mbr_aux.tiempo);

if(strcasecmp(mbr_aux.p1.estado,"0")==0){
    disponibles=disponibles+1;
}

if(strcasecmp(mbr_aux.p2.estado,"0")==0){
    disponibles=disponibles+1;
}

if(strcasecmp(mbr_aux.p3.estado,"0")==0){
    disponibles=disponibles+1;
}

if(strcasecmp(mbr_aux.p4.estado,"0")==0){
    disponibles=disponibles+1;
}

//REVISANDO LA DISPONIBILIDAD
if(disponibles==4){
//SIGINIFICA QUE NO HAY PARTICIONES EN EL DISCO
if(strcasecmp(unidad,"B")==0) {
mbr_aux.p1.tam=tparticion;
}else if(strcasecmp(unidad,"K")==0 || strcasecmp(unidad,"")==0){
tparticion=tparticion*1000;
mbr_aux.p1.tam=tparticion;
}else if(strcasecmp(unidad,"M")==0){
tparticion=tparticion*1000*1000;
mbr_aux.p1.tam=tparticion;
}
int tpivote=mbr_aux.mbr_tam-sizeof(MBR);
//VERIFICO EL TAMAÑO SI NO SOBREPASA AL DISCO
if(tparticion<=tpivote){
strcpy(mbr_aux.p1.estado,"1");
if(strcasecmp(fit,"")==0){
strcpy(fit,"WF");
}

printf("\n EL ESTADO DE LA PRIMERA PARTICION ES: %s", mbr_aux.p1.estado);
printf("\n EL ESTADO DE LA SEGUNDA PARTICION ES: %s", mbr_aux.p2.estado);
printf("\n EL ESTADO DE LA TERCERA PARTICION ES: %s", mbr_aux.p3.estado);
printf("\n EL ESTADO DE LA CUARTA PARTICION ES: %s", mbr_aux.p4.estado);

strcpy(mbr_aux.p1.fit,fit);
mbr_aux.p1.inicio=sizeof(MBR);
strcpy(mbr_aux.p1.nombre,nombreArchivo);
strcpy(mbr_aux.p1.tipo,tipo);

//FILE *escritor2= fopen(pathArchivo,"wb+");
fseek(fr2,0,SEEK_SET);
fwrite(&mbr_aux,sizeof(MBR),1,fr2);

fseek(fr2,mbr_aux.p1.tam+sizeof(MBR),SEEK_SET);
fwrite(&mbr_aux.p1,sizeof(particion),1,fr2);

fclose(fr2);
}else{
printf("\nLA PARTICION SOBREPASA EL TAMAÑO DEL ARCHIVO, VERIFIQUE");
}
}else if(disponibles==3){

if(strcasecmp(unidad,"B")==0) {
mbr_aux.p2.tam=tparticion;
}else if(strcasecmp(unidad,"K")==0 || strcasecmp(unidad,"")==0){
tparticion=tparticion*1000;
mbr_aux.p2.tam=tparticion;
}else if(strcasecmp(unidad,"M")==0){
tparticion=tparticion*1000*1000;
mbr_aux.p2.tam=tparticion;
}

int tpivote=mbr_aux.mbr_tam-(sizeof(MBR)+mbr_aux.p1.tam);
//VERIFICO EL TAMAÑO SI NO SOBREPASA AL DISCO
if(tparticion<=tpivote){
strcpy(mbr_aux.p2.estado,"1");
if(strcasecmp(fit,"")==0){
strcpy(fit,"WF");
}

printf("\n EL ESTADO DE LA PRIMERA PARTICION ES: %s", mbr_aux.p1.estado);
printf("\n EL ESTADO DE LA SEGUNDA PARTICION ES: %s", mbr_aux.p2.estado);
printf("\n EL ESTADO DE LA TERCERA PARTICION ES: %s", mbr_aux.p3.estado);
printf("\n EL ESTADO DE LA CUARTA PARTICION ES: %s", mbr_aux.p4.estado);

strcpy(mbr_aux.p2.fit,fit);
mbr_aux.p2.inicio=sizeof(MBR)+mbr_aux.p1.tam;
strcpy(mbr_aux.p2.nombre,nombreArchivo);
strcpy(mbr_aux.p2.tipo,tipo);

fseek(fr2,0,SEEK_SET);
fwrite(&mbr_aux,sizeof(MBR),1,fr2);

fseek(fr2,mbr_aux.p1.tam+mbr_aux.p2.tam+sizeof(MBR),SEEK_SET);
fwrite(&mbr_aux.p2,sizeof(particion),1,fr2);

fclose(fr2);

}else{
printf("LA PARTICION SOBREPASA EL TAMAÑO DEL ARCHIVO, VERIFIQUE");
}
}else if(disponibles==2){
if(strcasecmp(unidad,"B")==0) {
mbr_aux.p3.tam=tparticion;
}else if(strcasecmp(unidad,"K")==0 || strcasecmp(unidad,"")==0){
tparticion=tparticion*1000;
mbr_aux.p3.tam=tparticion;
}else if(strcasecmp(unidad,"M")==0){
tparticion=tparticion*1000*1000;
mbr_aux.p3.tam=tparticion;
}

int tpivote=mbr_aux.mbr_tam-(sizeof(MBR)+mbr_aux.p1.tam+mbr_aux.p2.tam);
//VERIFICO EL TAMAÑO SI NO SOBREPASA AL DISCO
if(tparticion<=tpivote){
strcpy(mbr_aux.p3.estado,"1");
if(strcasecmp(fit,"")==0){
strcpy(fit,"WF");
}

printf("\n EL ESTADO DE LA PRIMERA PARTICION ES: %s", mbr_aux.p1.estado);
printf("\n EL ESTADO DE LA SEGUNDA PARTICION ES: %s", mbr_aux.p2.estado);
printf("\n EL ESTADO DE LA TERCERA PARTICION ES: %s", mbr_aux.p3.estado);
printf("\n EL ESTADO DE LA CUARTA PARTICION ES: %s", mbr_aux.p4.estado);

strcpy(mbr_aux.p3.fit,fit);
mbr_aux.p3.inicio=sizeof(MBR)+mbr_aux.p1.tam+mbr_aux.p2.tam;
strcpy(mbr_aux.p3.nombre,nombreArchivo);
strcpy(mbr_aux.p3.tipo,tipo);

fseek(fr2,0,SEEK_SET);
fwrite(&mbr_aux,sizeof(MBR),1,fr2);

fseek(fr2,mbr_aux.p1.tam+mbr_aux.p2.tam+mbr_aux.p3.tam+sizeof(MBR),SEEK_SET);
fwrite(&mbr_aux.p3,sizeof(particion),1,fr2);

fclose(fr2);

}else{
printf("LA PARTICION SOBREPASA EL TAMAÑO DEL ARCHIVO, VERIFIQUE");
}
}else if(disponibles==1){
if(strcasecmp(unidad,"B")==0) {
mbr_aux.p4.tam=tparticion;
}else if(strcasecmp(unidad,"K")==0 || strcasecmp(unidad,"")==0){
tparticion=tparticion*1000;
mbr_aux.p4.tam=tparticion;
}else if(strcasecmp(unidad,"M")==0){
tparticion=tparticion*1000*1000;
mbr_aux.p4.tam=tparticion;
}

int tpivote=mbr_aux.mbr_tam-(sizeof(MBR)+mbr_aux.p1.tam+mbr_aux.p2.tam+mbr_aux.p3.tam);
//VERIFICO EL TAMAÑO SI NO SOBREPASA AL DISCO
if(tparticion<=tpivote){
strcpy(mbr_aux.p4.estado,"1");
if(strcasecmp(fit,"")==0){
strcpy(fit,"WF");
}

printf("\n EL ESTADO DE LA PRIMERA PARTICION ES: %s", mbr_aux.p1.estado);
printf("\n EL ESTADO DE LA SEGUNDA PARTICION ES: %s", mbr_aux.p2.estado);
printf("\n EL ESTADO DE LA TERCERA PARTICION ES: %s", mbr_aux.p3.estado);
printf("\n EL ESTADO DE LA CUARTA PARTICION ES: %s", mbr_aux.p4.estado);

strcpy(mbr_aux.p4.fit,fit);
mbr_aux.p4.inicio=sizeof(MBR)+mbr_aux.p1.tam+mbr_aux.p2.tam+mbr_aux.p3.tam;
strcpy(mbr_aux.p4.nombre,nombreArchivo);
strcpy(mbr_aux.p4.tipo,tipo);

fseek(fr2,0,SEEK_SET);
fwrite(&mbr_aux,sizeof(MBR),1,fr2);

fseek(fr2,mbr_aux.p1.tam+mbr_aux.p2.tam+mbr_aux.p3.tam+mbr_aux.p4.tam+sizeof(MBR),SEEK_SET);
fwrite(&mbr_aux.p4,sizeof(particion),1,fr2);

fclose(fr2);

}else{
printf("LA PARTICION SOBREPASA EL TAMAÑO DEL ARCHIVO, VERIFIQUE");
}
}else{
printf("\n SE HAN CREADO LAS PARTICIONES PERMITIDAS, NO SE PUEDEN CREAR MAS");
}
}
}

void BorrarDiscoDuro(){
nodoc *aux= nodocomando;
char pathArchivo[80];
char comparador[40];
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"path")==0){
printf("\n YO DOY LA PATH Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(pathArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}
int lpath= strlen(pathArchivo);

char *separador=NULL;
separador= strtok(pathArchivo,"\"");
strcpy(pathArchivo,substr(separador,0,strlen(separador)));

printf(" \n %s",pathArchivo);

remove(pathArchivo);

}

void DiscoDuro(){
FILE *f;
FILE *file;
char escritor[1000]="\0";
char comparador[40];
char nombreArchivo[50];
char pathArchivo[80];
char tama[20];
char unidad[1];
nodoc *aux=nodocomando;
//PRIMER WHILE PARA EL TAMAÑO
while(aux!=NULL){
int td;
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"size")==0){
printf("YO DOY EL TAMAÑO y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(tama,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}
//WHILE PARA ENCONTRAR EL NOMBRE
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"name")==0){
printf("\n YO DOY EL NOMBRE y es : %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(nombreArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA ENCONTRAR LA PATH
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"path")==0){
printf("\n YO DOY LA PATH Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(pathArchivo,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//WHILE PARA ENCONTRAR LA UNIDAD
aux=nodocomando;
while(aux!=NULL){
strcpy(comparador,substr(aux->comando,1,4));
if(strcasecmp(comparador,"unit")==0){
printf("\n YO DOY LA UNIDAD Y ES: %s",substr(aux->comando,7,sizeof(aux->comando)));
strcpy(unidad,substr(aux->comando,7,sizeof(aux->comando)));
}
aux=aux->siguiente;
}

//QUITANDO LAS COMILLAS AL NOMBRE
char *sep1=NULL;
sep1= strtok(nombreArchivo,"\"");
strcpy(nombreArchivo,sep1);

//QUITANDO LAS COMILLAS AL PATH PARA HACER EL DIRECTORIO PRIMERO
char *separador=NULL;
separador= strtok(pathArchivo,"\"");
strcpy(pathArchivo,separador);
mkdir(pathArchivo,0777);


 strcat(pathArchivo,"/");
 strcat(pathArchivo,nombreArchivo);

f=fopen(pathArchivo,"wb+");
int c=0;
int tamArchivo;
tamArchivo=atoi(tama);

MBR NuevoDisco;
if(strcasecmp(unidad,"m\n")==0 || strcasecmp(unidad,"m")==0 || strcasecmp(unidad,"")==0){
NuevoDisco.mbr_tam=tamArchivo*1000*1000;
for(c;c<1000*tamArchivo;c++){
fwrite(escritor,sizeof(escritor),1,f);
}
//fclose (f);
}else if(strcasecmp(unidad,"k\n")==0 || strcasecmp(unidad,"k")==0){
NuevoDisco.mbr_tam=tamArchivo*1000;
for(c;c<tamArchivo;c++){
fwrite(escritor,sizeof(escritor),1,f);
}
//fclose (f);
}
//file=fopen(nombreArchivo,"wbr+");
int numero;
numero = rand () % 50 + 1;
NuevoDisco.numDisco=numero;
time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);
char output[100];
strftime(output,100,"%d/%m/%y %H:%M:%S",tlocal);

strcpy(NuevoDisco.p1.estado,"0");
strcpy(NuevoDisco.p2.estado,"0");
strcpy(NuevoDisco.p3.estado,"0");
strcpy(NuevoDisco.p4.estado,"0");

strcpy(NuevoDisco.tiempo,output);


fseek(f,0,SEEK_SET);
fwrite(&NuevoDisco,sizeof(MBR),1,f);
fclose(f);
//printf("\n %d",td);
//printf("\n %s",nombreArchivo);
}



int main()
{

    nodocomando= IniciarListaComandos(nodocomando);
    llamada();

    return 0;
}
