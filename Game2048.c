
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Variables globales
int MatrizJuego[4][4],  CondicionVictoria=0;
char InstruccionUtilizada;

//Funciones auxiliares
void imprimir_grid();

bool detecto_numero(int POS1, int POS2);

int detecto_celdas_vacias();

bool detecto_grid(int POS1, int POS2, char comando);

bool num_siguiente(int POS1, int POS2,char comando);

//Funciones movimiento
void movimiento_validoY(int POS1,int POS2, char comando);

void movimiento_validoX(int POS1, int POS2, char comando);

void lectura_comando();

void ejecuto_movimiento();

//Funciones de colisiones y generacion
int generacion_aleatoria();

void asignacion_aleatoria();

void colisionY(int Matriz[][4]);

void colisionX(int Matriz[][4]);

void ejecuto_colision();

//Funcion de victoria/derrota

void detecto_derrota();


int main(){
    int POS1, POS2, maximo=0;
    srand(time(NULL));
    //Mensaje de bienvenida
    printf("Bienvenido al juego 2048\n");

    //Asignacion a la matriz inicial
    for(POS1=0; POS1<4; POS1++)
        for(POS2=0; POS2<4; POS2++)
            MatrizJuego[POS1][POS2]=1;
    asignacion_aleatoria(); //Asi empieza con un numero
    asignacion_aleatoria();

    //Impresion >> Lecturas del comando >> Movimientos >> Colision >> Asignacion aleatoria >> Fin loop
    while(CondicionVictoria==0){
        imprimir_grid();
        lectura_comando();
        ejecuto_movimiento();
        ejecuto_colision();
        ejecuto_movimiento();       //Ajuste por colision (cuando colisiona un numero se multiplica y una celda se vacia, por eso un movimiento fantasma de ajuste)
        asignacion_aleatoria();     //Solo si hay celdas vacias lo asigna
        //Una vez que termina de hacer todo lo que tiene que hacer entra en detecto derrota
        if(detecto_celdas_vacias()<1)
            detecto_derrota();

    }
    //Puntaje muestra matriz final y puntaje
    imprimir_grid();
    for(POS1=0;POS1<4;POS1++){
        for(POS2=0;POS2<4;POS2++){
            if(MatrizJuego[POS1][POS2]>maximo)
                maximo=MatrizJuego[POS1][POS2];
        }
    }
    if(maximo>=2048)
        printf("Felicitaciones ganaste");
    else
        printf("Perdiste, con un puntaje de %d", maximo);

    return 0;

}

///Procedimiento: para imprimir una grid cuadrada
void imprimir_grid(){
    int POS1, POS2;
    printf("\n---------------------\n");
    for(POS1=0; POS1<4; POS1++) {
        for(POS2=0; POS2<4; POS2++)
            if(MatrizJuego[POS1][POS2]==1)
                printf("|    ");
            else
                printf("|%4d", MatrizJuego[POS1][POS2]);
    printf("|\n---------------------\n");
    }
}
///Funcion: Detecto numero en la posicion 0x0
bool detecto_numero(int POS1, int POS2){
    bool numero=false;
    if(MatrizJuego[POS1][POS2]==1)
        numero=false;
    else
        numero=true;

    return numero;
}
///Funcion: Devuelve el numero de celdas vacias (para evitar colisiones y condicion de victoria/derrota)
int detecto_celdas_vacias(){
    int POS1, POS2, contadorVacio=0;
    for(POS1=0; POS1<4; POS1++)
        for(POS2=0; POS2<4; POS2++)
            if(MatrizJuego[POS1][POS2]==1)
                contadorVacio++;

    return contadorVacio;
}
///Funcion: Detecto grid para alguna direccion (4x4)
bool detecto_grid(int POS1,int POS2, char comando){
    bool valido=true;
    //Si se sale del grid
    if((POS1-1<0 && comando=='W') || (POS1+1>3 && comando=='S'))
        valido=false;
    if((POS2-1<0 && comando=='A') || (POS2+1>3 && comando=='D'))
        valido=false;
    return valido;
}
///Funcion: Detecto el siguiente numero para un eje
bool num_siguiente(int POS1, int POS2,char comando){
    bool numero=false;
    if(detecto_grid(POS1, POS2, comando)){
        switch(comando){
            case 'W':POS1--;break;
            case 'S':POS1++;break;
            case 'D':POS2++;break;
            case 'A':POS2--;break;
        }
        if((detecto_numero(POS1, POS2)) && (comando=='W' || comando=='S'))
            numero=true;
        else if((detecto_numero(POS1, POS2)) && (comando=='D' || comando=='A'))
            numero=true;
    }
    return numero;
}
///Procedimiento: Hasta donde puede mueve el numero en el eje vertical (Y)
void movimiento_validoY(int POS1,int POS2, char comando){
    int NumMovido;
    NumMovido=MatrizJuego[POS1][POS2];
    MatrizJuego[POS1][POS2]=1;

    while((detecto_grid(POS1, POS2, comando)) && !(num_siguiente(POS1, POS2, comando))){
        if(comando=='W')
            POS1--;
        else if(comando=='S')
            POS1++;
        }
    MatrizJuego[POS1][POS2]=NumMovido;
}
///Procedimiento: Idem anterior, (X)
void movimiento_validoX(int POS1, int POS2, char comando){
    int NumMovido;
    NumMovido=MatrizJuego[POS1][POS2];
    MatrizJuego[POS1][POS2]=1;

    while((detecto_grid(POS1, POS2, comando)) && !(num_siguiente(POS1, POS2, comando))){
        if(comando=='A')
            POS2--;
        else if(comando=='D')
            POS2++;
        }
    MatrizJuego[POS1][POS2]=NumMovido;
}
///Procedimiento lectura de comando ingresado
void lectura_comando(){
    bool lectura=false;
    char comando, letrabuffer;

    while(lectura==false){
        printf("\nIngrese su comando (W,S,D,A):\n");
        comando=getchar();
        letrabuffer=getchar();
        if(letrabuffer=='\n')
            switch(comando){
                case 'W':
                case 'S':
                case 'D':
                case 'A':
                    lectura=true;
                    InstruccionUtilizada=comando; //Variable Global para funciones (colision y movimiento)
                break;
                default:
                    printf("Entrada invalida, comando incorrecto, vuelva a intentarlo con (W,S,A,D).\n");
                    lectura=false;
                break;

            }
        else
            printf("Entrada no valida por saturacion. Intente con menos teclas y mas paciencia\n");
    //Leo el buffer de igual manera antes de salir del while
    while(letrabuffer!='\n')
        letrabuffer=getchar();
    }
}
///Procedimiento, lee movimiento y lo ejectuta
void ejecuto_movimiento(){

    int POS1, POS2;
    char instruccion=InstruccionUtilizada;

    //Necesita recorrer la matriz de forma adecuada para cada comando
    //Recorrido normal
    if(instruccion=='W')
        for(POS1=0; POS1<4; POS1++)
            for(POS2=0; POS2<4; POS2++)
                movimiento_validoY(POS1, POS2, instruccion);
    //Recorrido decreciente
    else if(instruccion=='S')
        for(POS1=3; POS1>=0; POS1--)
            for(POS2=3; POS2>=0; POS2--)
                movimiento_validoY(POS1, POS2, instruccion);
    //Recorrido invertido decreciente
    else if(instruccion=='D')
        for(POS1=3; POS1>=0; POS1--)
            for(POS2=3; POS2>=0; POS2--)
                movimiento_validoX(POS1, POS2, instruccion);
    //Recorrido normal
    else if(instruccion=='A')
        for(POS1=0; POS1<4; POS1++)
            for(POS2=0; POS2<4; POS2++)
                movimiento_validoX(POS1, POS2, instruccion);

}
///Funcion: Genera un 2 o un 4
int generacion_aleatoria(){
    int numero;
    numero=rand()%2;
    if(numero==0)
        numero=2;
    else
        numero=4;
return numero;
}
///Procedimiento: asigna un 2 o un 4 en una celda vacia aleatoria.
void asignacion_aleatoria(){
    int pos1, pos2, intentos=500;

    while(intentos>0 && detecto_celdas_vacias()>0){                     //Mientras que haya intentos y celdas vacias hace algo, numero de intentos es tan alto para evitar el caso improbable de que no salga la celda vacia
        pos1=rand()%4;
        pos2=rand()%4;
        if(!(detecto_numero(pos1, pos2)) && detecto_celdas_vacias()>0){ //Lee una posicion, si lee '1' devuelve falso (esta vacia), cuando es verdadera hay un numero y sobreescribe, por eso su complemento '!'
            MatrizJuego[pos1][pos2]=generacion_aleatoria();
            intentos=0;                                                 //Bandera de salida para el while
        }
    intentos--;
    }
}
///Procedimiento: Genera una colision en el eje Y
void colisionY(int MatrizJuego[][4]){
    bool CasillaCambiada[4];
    int posB, POS1, POS2;
    char comando;

    comando=InstruccionUtilizada;

    switch(comando){
        case 'W':
            for(POS2=0; POS2<4; POS2++){
                for(posB=0; posB<4; posB++)  //Inicializo el arreglo de verdad para manejar casos particulares
                    CasillaCambiada[posB]=false;
                for(POS1=0; POS1<=2; POS1++){    //Son 3 instancias que checkea este for (elementos primera columna: 0x1, 1x2, 2x3)
                    if((MatrizJuego[POS1][POS2] != 1 && MatrizJuego[POS1+1][POS2] != 1))
                        if(MatrizJuego[POS1][POS2]==MatrizJuego[POS1+1][POS2] && CasillaCambiada[POS1]==false && CasillaCambiada[POS1+1]==false){
                            MatrizJuego[POS1][POS2]*=2;
                            MatrizJuego[POS1+1][POS2]=1;
                            CasillaCambiada[POS1+1]=true;
                            CasillaCambiada[POS1]=true;
                            if(MatrizJuego[POS1][POS2]==2048)
                                CondicionVictoria=1;
                        }
                }
            }
        break;
        case 'S':
        for(POS2=0; POS2<4; POS2++){
            for(posB=0; posB<4; posB++)
                CasillaCambiada[posB]=false;
            for(POS1=3; POS1>=1; POS1--){    //Son 3 instancias que checkea este for (elementos primera columna: 3x2, 2x1, 0x1)
                if((MatrizJuego[POS1][POS2] != 1 && MatrizJuego[POS1-1][POS2] != 1))
                    if(MatrizJuego[POS1][POS2]==MatrizJuego[POS1-1][POS2] && CasillaCambiada[POS1]==false && CasillaCambiada[POS1-1]==false){
                        MatrizJuego[POS1-1][POS2]=1;    //Pos ejemplo 2, queda vacio
                        MatrizJuego[POS1][POS2]*=2;     //Pos ejemplo 3, doble
                        CasillaCambiada[POS1]=true;
                        CasillaCambiada[POS1-1]=true;
                        if(MatrizJuego[POS1][POS2]==2048)
                            CondicionVictoria=1;
                    }
            }//End FOR POS1!!!
        }//End FOR POS2!!!
        break;
    }//End Switch
}
///Procedimiento: Genera una colision en el eje X
void colisionX(int MatrizJuego[][4]){
    ///Misma logica que la colision Y pero aplicada para Eje X (comandos 'D'/'A')
    bool CasillaCambiada[4];
    int posB, POS1, POS2;
    char comando;

    comando=InstruccionUtilizada;

    switch(comando){
        case 'D':
            for(POS1=0; POS1<4; POS1++){
                for(posB=0; posB<4; posB++)
                    CasillaCambiada[posB]=false;
                for(POS2=0; POS2<=2; POS2++){
                    if(MatrizJuego[POS1][POS2] != 1 && MatrizJuego[POS1][POS2+1] != 1  )
                        if(MatrizJuego[POS1][POS2]==MatrizJuego[POS1][POS2+1] && CasillaCambiada[POS2]==false && CasillaCambiada[POS2+1]==false){
                            MatrizJuego[POS1][POS2]=1;
                            MatrizJuego[POS1][POS2+1]*=2;
                            CasillaCambiada[POS2]=true;
                            CasillaCambiada[POS2+1]=true;
                            if(MatrizJuego[POS1][POS2+1]==2048)
                                CondicionVictoria=1;
                        }
                }
            }
        break;
        case 'A':
            for(POS1=0; POS1<4; POS1++){
                for(posB=3; posB>=0; posB--)
                    CasillaCambiada[posB]=false;
            for(POS2=3; POS2>=1; POS2--){
                if(MatrizJuego[POS1][POS2] != 1 && MatrizJuego[POS1][POS2-1] != 1)
                    if(MatrizJuego[POS1][POS2]==MatrizJuego[POS1][POS2-1] &&  CasillaCambiada[POS2]==false && CasillaCambiada[POS2-1]==false){
                        MatrizJuego[POS1][POS2-1]*=2;
                        MatrizJuego[POS1][POS2]=1;
                        CasillaCambiada[POS2]=true;
                        CasillaCambiada[POS2-1]=true;
                        if(MatrizJuego[POS1][POS2-1]==2048)
                            CondicionVictoria=1;
                    }
            }//FIN DE FOR POS2!!!
        }//FIN DE FOR POS2!!!
        break;
    }//FIN DE Switch
}
///Procedimiento: Invoca las funciones de colision para el eje X e Y
void ejecuto_colision(){

    //Instruccion Utilizable: Variable Global (generada en lectura comando para movimiento)
    if(InstruccionUtilizada=='W' || InstruccionUtilizada=='S')
        colisionY(MatrizJuego);
    else{
        if(InstruccionUtilizada=='D' || InstruccionUtilizada=='A')
            colisionX(MatrizJuego);
    }
}
///Procedimiento, ve si la MatrizJuego copiada, hace colisiones y hay celdas vacias, si hay se sigue jugando
void detecto_derrota(){
    int POS1, POS2;
    int MatrizNemesis[4][4];
    char comando_inicial;

    //Inicializo a la matriz clon
    for(POS1=0; POS1<4; POS1++)
        for(POS2=0; POS2<4; POS2++)
            MatrizNemesis[POS1][POS2]=MatrizJuego[POS1][POS2];
    //La muevo
    comando_inicial=InstruccionUtilizada;
    InstruccionUtilizada='W';
    colisionY(MatrizNemesis);
    InstruccionUtilizada='D';
    colisionX(MatrizNemesis);

    InstruccionUtilizada=comando_inicial;

    //Ejecuta sentencia se asume que pierde, si son diferentes luego de haber movido (W-S-D-A) o hay un espacio vacio, para la busqueda y sigue jugando (CondicionVictoria a 0)
    //Sino CondicionVictoria=-1 y el programa sale del loop
    CondicionVictoria=-1;
    POS1=0;
    while(POS1<4){
        POS2=0;
        while(POS2<4){
            if(MatrizNemesis[POS1][POS2]==1 || MatrizJuego[POS1][POS2]==1){
                CondicionVictoria=0;
            }
            POS2++;
        }
        POS1++;
    }
}



