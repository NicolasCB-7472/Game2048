#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

///>>>ENTREGA 2<<<///

//Constantes
#define TAM_AR 21///Para nombre,apellido (+1 para '/0')
#define NICK_AR 6///Para nick (+1 para '/0')

//Estructuras
typedef struct Puntos_Puntaje_{
    int PARTIDA1;
    int PARTIDA2;
    int PARTIDA3;
    int sesionesTotal;
    int puntosTotal;
}Puntos_Puntaje;

typedef struct Usuario_User_{
    char alias[NICK_AR];
    char nombre[TAM_AR];
    char apellido[TAM_AR];
    int edad;
    bool estadoActivo;
    Puntos_Puntaje Jugador_Puntaje;
}Usuario_User;

//Variables Globales
int POS_USER_GLOBAL=0, JUGADOR_GLOBAL=-1;
Usuario_User Jugadores_User[10];

//Funciones y procedimientos
///Procedimiento para la lectura de una linea
void leer_linea(char arr[], int tam);

///Funcion: Checkea si el alias es unico
bool alias_unico(char alias[],int numAlias);

///Procedimiento: Registra un usuario en una posicion global
void registrar_user();

///Procedimiento: Impresion de todos los usuarios
void listado_user();

///Procedimiento: Inicializa el estado de todos los jugadores en falso
void desactivarJugadores();
    
///Procedimiento: Inicia el 2048
void iniciar_juego();

///Procedimiento: Buscar jugador e imprimir datos
void buscar_user();

///Procedimiento: Eliminar jugador con nick
void eliminar_user();

int main(){
    
    desactivarJugadores();
    registrar_user();
    listado_user();
    eliminar_user();
    buscar_user();
    //iniciar_juego();
    return 0;
}

///FUNCIONES///

///Lectura linea
void leer_linea(char arr[], int tam){
    int pos=-1;
    do{
   	 if(pos<tam-1)
   		 pos++;
   	 arr[pos]=getchar();    
    }while(arr[pos]!='\n');
    arr[pos]='\0';
}
///Funcion: Checkea si el alias es unico
bool alias_unico(char alias[],int numAlias){
    bool unico=true;
    int  POS=0;
    while(POS>=0 && POS<10 && unico==true){
   	 if(strcmp(alias, Jugadores_User[POS].alias) == 0)    //Mismo nombre?
   		 if(POS != numAlias){   						 //Dif lugar de comparacion?
   			 unico=false;
   			 JUGADOR_GLOBAL=POS;   					 //Para buscar_user se necesita esta posicion.
   		 }   										 //Y para eliminar_user
   	 POS++;
    }
    return unico;
}

///Registrar un usuario con posicion
void registrar_user(){
    int POS=0;
    //TAM_AR largo del arreglo (constante), idem con NICK_AR
    
    while(Jugadores_User[POS].estadoActivo == true && POS<10){
   	  POS++;
    }
    POS_USER_GLOBAL=POS;
    
    if(POS_USER_GLOBAL<10){
   	 printf("\n>>PORFAVOR COMPLETAR DATOS<<\n");
   	 printf("Ingrese su alias:");
   	 leer_linea(Jugadores_User[POS_USER_GLOBAL].alias, NICK_AR);
   	 if(alias_unico(Jugadores_User[POS_USER_GLOBAL].alias, POS_USER_GLOBAL)){
   		 printf("Ingrese su nombre:");
   		 leer_linea(Jugadores_User[POS_USER_GLOBAL].nombre, TAM_AR);
   		 printf("Ingresu su apellido:");
   		 leer_linea(Jugadores_User[POS_USER_GLOBAL].apellido, TAM_AR);
   		 printf("Ingrese su edad:");
   		 scanf("%d", &Jugadores_User[POS_USER_GLOBAL].edad);getchar();
   		 
   		 Jugadores_User[POS_USER_GLOBAL].estadoActivo=true;
   		 POS_USER_GLOBAL++;
   		 printf("\n");
   	 }else
   		 printf(">>>Alias ocupado, complete la registracion nuevamente<<<\n");
    }else
   	 printf("\n>>>Cantidad maxima de usuarios<<<\n");
}

///Impresion de todos los usuarios
void listado_user(){
    int POS;
    if(POS_USER_GLOBAL>0){ //Es 1 si hay alguien registrado
   	 printf("\nJUGADOR|PUNTAJE\n");
   	 printf("_________________\n");
   	 for(POS=0; POS<10; POS++){
   		 if(Jugadores_User[POS].estadoActivo){ //estadoActivo es una expresion booleana
   			 printf("%7s|", Jugadores_User[POS].alias);
   			 printf(" %6d.|\n", Jugadores_User[POS].Jugador_Puntaje.puntosTotal);
   		 }    
   	 }
   	 printf("-------|--------|\n");
    }
    else
   	 printf("\n>>>Error 404: No se encontraron jugadores registrados<<<\n");
}

///Inicializa el estado de todos los jugadores en falso
void desactivarJugadores(){
    int POS;
    
    for(POS=0; POS<10; POS++){
   	 Jugadores_User[POS].estadoActivo=false;
   	 Jugadores_User[POS].Jugador_Puntaje.puntosTotal=0;
   	 Jugadores_User[POS].Jugador_Puntaje.PARTIDA1=0;
   	 Jugadores_User[POS].Jugador_Puntaje.PARTIDA2=0;
   	 Jugadores_User[POS].Jugador_Puntaje.PARTIDA3=0;
   	 Jugadores_User[POS].Jugador_Puntaje.sesionesTotal=0;
    }
    
}
    
///Inicia el 2048
void iniciar_juego(){
    char candidato[NICK_AR];
    JUGADOR_GLOBAL=-1; //Idem siguiente, -1 para evitar comparar en su posicion actual
    printf("\nHola, quien eres? Puedes usar tu alias para identificarte: ");
    leer_linea(candidato, NICK_AR);
    if(!alias_unico(candidato,JUGADOR_GLOBAL) && Jugadores_User[JUGADOR_GLOBAL].estadoActivo ){
   	 printf("\nBienvenido te deseo mucha suerte ");
   	 printf("%s ", Jugadores_User[JUGADOR_GLOBAL].nombre);
   	 printf("%s!\n", Jugadores_User[JUGADOR_GLOBAL].apellido);
   	 Jugadores_User[JUGADOR_GLOBAL].Jugador_Puntaje.sesionesTotal++;
   	 //juego 2048
    }else
   	 printf("\n>>>Usuario no reconocido<<<\n");
}



///Procedimiento: Buscar jugador e imprimir datos
void buscar_user(){
    char candidato[NICK_AR];
    printf("\nIngrese el NICK del usuario a buscar: ");
    leer_linea(candidato, NICK_AR);
    
    JUGADOR_GLOBAL=-1; //alias_unico usa un num para evitar comparar en su posicion actual
    //Si el alias no es unico, hay una coincidencia
    if(!alias_unico(candidato,JUGADOR_GLOBAL) && Jugadores_User[JUGADOR_GLOBAL].estadoActivo){
   	 if(JUGADOR_GLOBAL>=0 && JUGADOR_GLOBAL<10){    //Redundancia
   		 printf("Nombre: %s\n", Jugadores_User[JUGADOR_GLOBAL].nombre);
   		 printf("Apellido: %s\n", Jugadores_User[JUGADOR_GLOBAL].apellido);
   		 printf("Puntaje obtenido: %d\n", Jugadores_User[JUGADOR_GLOBAL].Jugador_Puntaje.puntosTotal);
   	 }else
   		 printf("\n>>>Nunca se deberia de llegar hasta aca<<<\n");
    }else    
   	 printf("\n>>>El alias ingresado no esta registrado<<<\n");
}


///Eliminar user
void eliminar_user(){
    char candidato[NICK_AR];
    
    printf("\nATENCION:Esta accion es permanente y no se hacen ninguna copia en la base de datos\n");
    printf("Ingrese el NICK de usuario a ELIMINAR permanentemente: ");
    leer_linea(candidato, NICK_AR);

    JUGADOR_GLOBAL=-1; //alias_unico usa un num para evitar comparar en su posicion actual
    //Si el alias no es unico, hay una coincidencia
    if(!alias_unico(candidato,JUGADOR_GLOBAL) && Jugadores_User[JUGADOR_GLOBAL].estadoActivo){
   	 if(JUGADOR_GLOBAL>=0 && JUGADOR_GLOBAL<10)    //Redundancia
   		 Jugadores_User[JUGADOR_GLOBAL].estadoActivo=false;
   	 else
   		 printf("\n>>>Nunca se deberia de llegar hasta aca<<<\n");
    }else    
   	 printf("\n>>>El alias no esta, no se elimino nada<<<\n");
}





