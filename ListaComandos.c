
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comandos.h"

nodoc *IniciarListaComandos(nodoc *primero){
primero= NULL;
return primero;
}

nodoc *CrearComando(char comand[50]){
nodoc *nuevo= (nodoc*)malloc(sizeof(nodoc));
strcpy(nuevo->comando,comand);
nuevo->siguiente=NULL;
return nuevo;
}

nodoc *InsertarComando(nodoc *primero, nodoc *nuevocomando){
if(primero==NULL){
primero=nuevocomando;
}else{
nuevocomando->siguiente = primero;
primero = nuevocomando;
}

return primero;
}


void ImprimirComandos(nodoc *primero){
    nodoc *actual = primero;
    printf("COLA DE COMANDOS \n");
    while(actual!= NULL){
        printf("%s",actual->comando);
        printf("\n");
        actual=actual->siguiente;
    }
}
