#include "LAB_2.h"

//Procedimiento que permite leer el archivo de entrada y retorna la cantidad de lineas que este contiene.
//Entrada: Char* que representa el nombre del archivo a leer.
//Salida: Int que representa la cantidad de lineas que posee el archivo de texto.
int readLines(char* fileName){
    FILE* file;
    int count = 0;
    char wordAux[50];
    
    file = fopen(fileName,"r");
    if(file == NULL){
        printf("El archivo no existe...\n");
        return 0;
    }
    else{
        while(!feof(file)){

            fscanf(file," %[^\n]",wordAux);
            count += 1;
        }
    }
    fclose(file);
    return count;
}

//Procedimiento que dado un struct TicTacToe, accede a la variable board para mostrar el contenido del array.
//Entrada: Struct TicTacToe con el tablero a mostrar.
//Salida: Vacia (Imprime por pantalla el tablero).
void showBoard(TicTacToe* ticTacToe){
    for(int i = 0; i < BOARD_LENGTH; i++){
        if(strcmp(ticTacToe->board[i],ticTacToe->playerX) == 0){
            printf("X ");
        }
        else if(strcmp(ticTacToe->board[i],ticTacToe->playerO) == 0){
            printf("O ");
        }
        else{
            printf("%s ",ticTacToe->board[i]);
        }
        if(i == 2 || i == 5){
            printf("\n");
        }
    }
    printf("\n\n");
}

//Procedimiento que dado un struct TicTacToe, toma la variable board y verifica si existe algun ganador. (Revisando las posiciones)
//Entrada: Struct TicTacToe con el tablero a verificar.
//Salida: Bool, true si existe un ganador, false en caso contrario.
bool verifyWinner(TicTacToe* ticTacToe){
    if( ((strcmp(ticTacToe->board[0],ticTacToe->board[1]) == 0) && (strcmp(ticTacToe->board[1],ticTacToe->board[2]) == 0) && (strcmp(ticTacToe->board[0],"V") != 0)) ||
        ((strcmp(ticTacToe->board[3],ticTacToe->board[4]) == 0) && (strcmp(ticTacToe->board[4],ticTacToe->board[5]) == 0) && (strcmp(ticTacToe->board[3],"V") != 0)) || 
        ((strcmp(ticTacToe->board[6],ticTacToe->board[7]) == 0) && (strcmp(ticTacToe->board[7],ticTacToe->board[8]) == 0) && (strcmp(ticTacToe->board[6],"V") != 0)) ||
        ((strcmp(ticTacToe->board[0],ticTacToe->board[3]) == 0) && (strcmp(ticTacToe->board[3],ticTacToe->board[6]) == 0) && (strcmp(ticTacToe->board[0],"V") != 0)) ||
        ((strcmp(ticTacToe->board[1],ticTacToe->board[4]) == 0) && (strcmp(ticTacToe->board[4],ticTacToe->board[7]) == 0) && (strcmp(ticTacToe->board[1],"V") != 0)) ||
        ((strcmp(ticTacToe->board[2],ticTacToe->board[5]) == 0) && (strcmp(ticTacToe->board[5],ticTacToe->board[8]) == 0) && (strcmp(ticTacToe->board[2],"V") != 0)) ||
        ((strcmp(ticTacToe->board[0],ticTacToe->board[4]) == 0) && (strcmp(ticTacToe->board[4],ticTacToe->board[8]) == 0) && (strcmp(ticTacToe->board[0],"V") != 0)) ||
        ((strcmp(ticTacToe->board[6],ticTacToe->board[4]) == 0) && (strcmp(ticTacToe->board[4],ticTacToe->board[2]) == 0) && (strcmp(ticTacToe->board[6],"V") != 0) ))
        {
            return true;
        }
    return false;
}

//Procedimiento que dado un struct PipeLine y un nombre de una instruccion mips, suma un 1 a la/s etapa/s del PipeLine que son utilizadas por la instruccion.
//Entrada: Struct PipeLine que representa el pipeLine del gato que se esta jugando, Char* instructionName que representa el nombre de la instruccion MIPS.
//Salida: Struct PipeLine con sus valores correspondientes actualizados.
PipeLine* updatePipeLine(PipeLine* pipeLine,char* instructionName){
    if( (strcmp(instructionName,"addi") == 0) || (strcmp(instructionName,"subi")== 0) ) {
        pipeLine->IF += 1;
        pipeLine->ID += 1;
        pipeLine->EX += 1;
        pipeLine->MEM += 0;
        pipeLine->WB += 1;
    }
    if(strcmp(instructionName,"sw") == 0 ){
        pipeLine->IF += 1;
        pipeLine->ID += 1;
        pipeLine->EX += 1;
        pipeLine->MEM += 1;
        pipeLine->WB += 0;
    }
    return pipeLine;
}

//Procedimiento que dado un struct PipeLine, muestra los valores (veces que se ha entrado a cada etapa) de este struct.
//Entrada: Struct PipeLine , que contiene la información a imprimir.
//Salida: Vacia (Imprime por pantalla el PipeLine).
void showPipeLine(PipeLine* pipeLine){
    printf("IF = %d\n",pipeLine->IF);
    printf("ID = %d\n",pipeLine->ID);
    printf("EX = %d\n",pipeLine->EX);
    printf("MEM = %d\n",pipeLine->MEM);
    printf("WB = %d\n",pipeLine->WB);
}

//Procedimiento que dado una instruccion MIPS, retorna el nombre de la instrucción MIPS
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Char* que representa el nombre de la instruccion MIPS.
char* getInstructionName(char* instruction){
    char* auxStr = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    auxStr = strtok(instructionAux," ,");
    return auxStr;
}

//Procedimiento que dado una instruccion MIPS, retorna el registro $rt de la instrucción MIPS
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Char* que representa el registro $rt de la instruccion MIPS.
char* getInstructionRT(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if((strcmp("addi",name) == 0) || (strcmp("subi",name) == 0)){
        result = strtok(instructionAux," ,()");
        result = strtok(NULL," ,()");
        return result;
    }
    else if (strcmp("sw",name) == 0){
        result = strtok(instructionAux," ,()");
        result = strtok(NULL," ,()");
        return result;
    }
    else{
        return "";
    }
}

//Procedimiento que dado una instruccion MIPS, retorna el registro $rs de la instrucción MIPS
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Char* que representa el registro $rs de la instruccion MIPS.
char* getInstructionRS(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if((strcmp("addi",name) == 0) || (strcmp("subi",name) == 0)){
        result = strtok(instructionAux," ,()");
        result = strtok(NULL," ,()");
        result = strtok(NULL," ,()");
        return result;
    }
    else if (strcmp("sw",name) == 0){
        result = strtok(instructionAux," ,()");
        result = strtok(NULL," ,()");
        result = strtok(NULL," ,()");
        result = strtok(NULL," ,()");
        return result;
    }
    else{
        return "";
    }
}

//Procedimiento que dado una instruccion MIPS, retorna el registro immediate, si es que existe, de la instrucción MIPS. En caso de no existir retorna un 0
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Int que representa el immediate de la instruccion MIPS.
int getInstructionImmediate(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if((strcmp("addi",name) == 0) || (strcmp("subi",name) == 0)){
        result = strtok(instructionAux," ,()");
        result = strtok(NULL," ,()");
        result = strtok(NULL," ,()");
        result = strtok(NULL," ,()");
        return atoi(result);
    }
    else{
        return 0;
    }
}

//Procedimiento que dado una instruccion MIPS, retorna el registro offset, si es que existe, de la instrucción MIPS. En caso de no existir retorna un 0
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Int que representa el offset de la instruccion MIPS.
int getInstructionOffset(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if(strcmp("sw",name) == 0){
        result = strtok(instructionAux," ,()");
        result = strtok(NULL," ,()");
        result = strtok(NULL," ,()");
        return atoi(result);
    }
    else{
        return 0;
    }
}

//Procedimiento que dado un Struct Instruction, lee el archivo y por cada linea (Instruccion MIPS) obtiene la informacion y la guarda dentro de las variables del Struct.
//Entrada: Char* que representa el nombre del archivo, Int que representa la cantidad de instrucciones, Struct Instruction que representa el struct donde se guardad la informacion.
//Salida: Un arreglo de Struct Instruction, que contiene, por cada posicion, la informacion de cada instruccion MIPS.
Instruction* readInstructions(char* fileName, int lengthInstructions,Instruction* instructionList){
    FILE* file;
    char wordAux[50];
    int i;
    for(int i = 0; i < lengthInstructions; i++){
        instructionList[i].name = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].rt = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].rs = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].offset = 0;
        instructionList[i].immediate = 0;
    }

    file = fopen(fileName,"r");
    if(file == NULL){
        printf("El archivo no existe...\n");
        return instructionList;
    }
    else{
        i = 0;
        while(!feof(file)){
            fscanf(file," %[^\n]",wordAux);
            strcpy(instructionList[i].name,getInstructionName(wordAux));
            strcpy(instructionList[i].rt,getInstructionRT(wordAux));
            strcpy(instructionList[i].rs,getInstructionRS(wordAux));
            instructionList[i].offset = getInstructionOffset(wordAux);
            instructionList[i].immediate = getInstructionImmediate(wordAux);
            i += 1;
            }
        }  
    fclose(file);
    return  instructionList;
}

//Procedimiento que dado un Struct Instruction, un Struct TicTacToe, un Struct PipeLine y un Int lengthInstructions, toma cada instruccion del arreglo de instrucciones
// y verifica si la jugada es valida, en caso de ser valida se actualiza el Struct TicTacToe y el Struct PipeLine.
//Entrada: Instruction* que es el arreglo de instrucciones MIPS, TicTacToe que representa el gato en donde se jugara, PipeLine que representa el pipeline de la jugada actual
//y Int que representa la cantidad de instrucciones.
//Salida: TicTacToe actualizado con las jugadas realizadas
TicTacToe* playTicTacToe(Instruction* instructionsArray,TicTacToe* ticTacToe,PipeLine* pipeLine,int lengthInstructions){
    //Se inicialiazan variables del pipeline en 0.
    pipeLine->IF = 0;
    pipeLine->ID = 0;
    pipeLine->EX = 0;
    pipeLine->MEM = 0;
    pipeLine->WB = 0;
    //Se da memoria a cada variable que compone al struct TicTacToe.
    ticTacToe->playerX = (char*)malloc(sizeof(char) * WORD);
    ticTacToe->playerO = (char*)malloc(sizeof(char) * WORD);
    ticTacToe->boardRegister = (char*)malloc(sizeof(char) * WORD);
    //Se inicializan variables auxiliares.
    bool boolAux = false;
    bool boolAux2 = false;
    int aux = 0;

    printf("\n");

    //Se empieza el Juego.

    //Se asigna el primer jugador a PlayerX
    strcpy(ticTacToe->playerX,instructionsArray[0].rt);
    //Se asigna el primer jugador a Player0
    strcpy(ticTacToe->playerO,instructionsArray[1].rt);

    //Se verifica si los registros donde se crea el array son coherentes.
    if( (strcmp(instructionsArray[2].rt,instructionsArray[2].rs) != 0) && (strcmp(instructionsArray[2].rs,"$zero") != 0) ){
        //Se avisa al usuario en caso de que las dimensiones del tablero no sean las correctas.
        printf("ERROR : REGISTROS PARA CREAR EL TABLERO NO SON COHERENTES... Instruccion %d\n",3);
        return ticTacToe;
    }
    //Se verifica si la tercera instruccion es la creacion del tablero y si esta sigue el formato adecuado.
    if( (strcmp(instructionsArray[2].name,"addi") == 0) && (strcmp(instructionsArray[2].rt,instructionsArray[2].rs) == 0) ){
        if(instructionsArray[2].immediate ==  atoi("-36")){
            //En caso de que se cumpla el registro %RT de la tercera instruccion sera el que se guardara como boardRegister.
            strcpy(ticTacToe->boardRegister,instructionsArray[2].rt);
            //Se procede a dar memoria para al tablero, simulando la instruccion MIPS.
            ticTacToe->board = (char**)malloc(sizeof(char*) * BOARD_LENGTH);
            for(int i = 0; i < BOARD_LENGTH; i++){
                ticTacToe->board[i] = (char*)malloc(sizeof(char) * WORD);
                strcpy(ticTacToe->board[i],"V");
            }
            //Se actualiza el boolAux a true para que las jugadas inicien desde la cuarta instrucción.
            boolAux = true;
        }
        else{
            //Se avisa al usuario en caso de que las dimensiones del tablero no sean las correctas.
            printf("ERROR : LA DIMENSION DEL TABLERO ES INCORRECTA... Instruccion %d\n\n",3);
            return ticTacToe;
        }
    }
    //En caso de que la tercera funcion no sea de creación de tablero, se asumira que las jugadas se realizan solamente con "addi" o "subi".
    else{
        //En primer lugar se dara memoria al tablero.
        ticTacToe->board = (char**)malloc(sizeof(char*) * BOARD_LENGTH);
        for(int i = 0; i < BOARD_LENGTH; i++){
            ticTacToe->board[i] = (char*)malloc(sizeof(char) * WORD);
            strcpy(ticTacToe->board[i],"V");
        }
    }
    //Para realizar cada jugada se leeran las instrucciones restantes.

    if(boolAux == true){
        //El FOR inicia desde 3 ya que se han usado las instrucciones que declaran jugadores y la instruccion que crea el arreglo.
        //Se actualiza el PipeLine con las 3 instrucciones que ya se han ejecutado.
        pipeLine = updatePipeLine(pipeLine,instructionsArray[0].name);
        pipeLine = updatePipeLine(pipeLine,instructionsArray[1].name);
        pipeLine = updatePipeLine(pipeLine,instructionsArray[2].name);
        for(int i = 3; i < lengthInstructions; i++){
                //Se obtiene el nombre de la instruccion para verificar si el immediate u offset esta dentro del rango del arreglo del gato.
                if(strcmp(instructionsArray[i].name,"addi") == 0){
                    //Se verifica si el immediate de la instruccion esta dentro del rango valido.
                    if((instructionsArray[i].immediate >= 0) && (instructionsArray[i].immediate <= 9)){
                        //Se verifica si el tablero en la posicion esta vacio (V).
                        if(strcmp(ticTacToe->board[instructionsArray[i].immediate - 1],"V") == 0){
                            //Como se pasan todas las verificaciones, se procede a realizar la jugada.
                            strcpy(ticTacToe->board[instructionsArray[i].immediate - 1],instructionsArray[i].rt);
                            //Pregunta si un jugador a ganado y si es que ya ha impreso la jugada ganadora.
                            if(aux == 0  && verifyWinner(ticTacToe)){
                                showBoard(ticTacToe);
                                //Validaciones para saber que jugador gano en que turno e informarle al usuario.
                                if(strcmp(instructionsArray[i].rt,ticTacToe->playerX) == 0){
                                    printf("Gano el jugador X en el turno %d\n\n", i - 2);
                                }
                                else{
                                    printf("Gano el jugador O en el turno %d\n\n", i - 2);
                                }
                                //Se actualizan variables auxiliares para el funcionamiento de procesamientos.
                                //Si boolAux2 es true, indica que existe un ganador en el juego.
                                boolAux2 = true;
                                //Aux es una variable que indica si ya se ha mostrado por pantalla el tablero donde gana un jugador.
                                aux = -1;
                            }
                        }
                        else{
                            //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                            printf("ERROR : TRATA DE SOBREESCRIBIR UNA JUGADA... Instruccion %d\n\n",i + 1);
                        }
                    }
                    else{
                        //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                        printf("ERROR : INSTRUCCION ADDII CON IMMEDIATE FUERA DE RANGO... Instruccion %d.\n\n",i + 1);
                    }
                    //Actualizacion contadores PipeLine
                    pipeLine = updatePipeLine(pipeLine,instructionsArray[i].name);
                }
                //Se obtiene el nombre de la instruccion para verificar si el immediate u offset esta dentro del rango del arreglo del gato.
                else if(strcmp(instructionsArray[i].name,"subi") == 0){
                    //Se verifica si el immediate de la instruccion esta dentro del rango valido.
                    if((instructionsArray[i].immediate >= 0) && (instructionsArray[i].immediate <= 9)){
                        //Se verifica si en la posicion en la cual se quiere borrar una jugada, corresponde a un movimiento anterior del mismo jugador.
                        if(strcmp(ticTacToe->board[instructionsArray[i].immediate - 1],instructionsArray[i].rt) == 0){
                            //En caso de que es el mismo jugador, se procede a eliminar dicha jugada.
                            strcpy(ticTacToe->board[instructionsArray[i].immediate - 1],"V");;
                        }
                        else{
                            //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                            printf("ERROR : TRATA DE ELIMINAR JUGADA QUE NO LE PERTENECE O NO EXISTE... Instruccion %d\n\n",i + 1);
                        }
                    }
                    else{
                        //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                        printf("ERROR : INSTRUCCION SUBI CON IMMEDIATE FUERA DE RANGO... Instruccion %d.\n\n",i + 1);
                    }
                    //Actualizacion contadores PipeLine
                    pipeLine = updatePipeLine(pipeLine,instructionsArray[i].name);
                }
                //En este else se considera la jugada realizada con "sw".
                //La jugada "sw" es solo considerada en este for ya que necesita la instruccion que crea el tablero para llevarse a cabo.
                else{
                    //Se obtiene el nombre de la instruccion para verificar si el immediate u offset esta dentro del rango del arreglo del gato.
                    if(strcmp(instructionsArray[i].name,"sw") == 0){
                        //Se verifica si el $rs de la instruccion "sw" correspode al $rs donde se creo el tablero.
                        if(strcmp(instructionsArray[i].rs,ticTacToe->boardRegister) == 0){
                            //Se verifica si el immediate de la instruccion esta dentro del rango valido y que corresponde a un multiplo de 4.
                            if((instructionsArray[i].offset >= 0) && (instructionsArray[i].offset <= 32) && (instructionsArray[i].offset % 4 == 0)){
                                //Se verifica si el tablero en la posicion esta vacio (V).
                                if(strcmp(ticTacToe->board[instructionsArray[i].offset / 4],"V") == 0){
                                    //Como se pasan todas las verificaciones, se procede a realizar la jugada.
                                    strcpy(ticTacToe->board[instructionsArray[i].offset / 4],instructionsArray[i].rt);
                                    //Pregunta si un jugador a ganado y si es que ya ha impreso la jugada ganadora.
                                    if(aux == 0  && verifyWinner(ticTacToe)){
                                        showBoard(ticTacToe);
                                        //Validaciones para saber que jugador gano en que turno e informarle al usuario.
                                        if(strcmp(instructionsArray[i].rt,ticTacToe->playerX) == 0){
                                            printf("Gano el jugador X en el turno %d\n\n", i - 2);
                                        }
                                        else{
                                            printf("Gano el jugador O en el turno %d\n\n", i - 2);
                                        }
                                        //Se actualizan variables auxiliares para el funcionamiento de procesamientos.
                                        //Si boolAux2 es true, indica que existe un ganador en el juego.
                                        boolAux2 = true;
                                        //Aux es una variable que indica si ya se ha mostrado por pantalla el tablero donde gana un jugador.
                                        aux = -1;
                                    }
                                }
                                else{
                                    //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                                    printf("ERROR : TRATA DE SOBREESCRIBIR UNA JUGADA... Instruccion %d\n\n",i + 1);
                                }
                            }
                            else{
                                //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                                printf("ERROR : INSTRUCCION SW CON OFFSET NO REPRESENTADO CON WORD O FUERA DE RANGO... Instruccion %d.\n\n",i + 1);
                            }
                        }
                        else{
                            //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                            printf("ERROR : INSTRUCCION SW CON $RS ERRONEO... Instruccion %d.\n\n",i + 1);
                        }
                        //Actualizacion contadores PipeLine
                        pipeLine = updatePipeLine(pipeLine,instructionsArray[i].name);
                    }
                }
        }
    }
    else{
        //El FOR inicia desde 2 ya que se han usado las instrucciones que daclaran jugadores.
        //Se actualiza el PipeLine con las 2 instrucciones que ya se han ejecutado.
        pipeLine = updatePipeLine(pipeLine,instructionsArray[0].name);
        pipeLine = updatePipeLine(pipeLine,instructionsArray[1].name);
        for(int i = 2; i < lengthInstructions; i++){
            //Se obtiene el nombre de la instruccion para verificar si el immediate u offset esta dentro del rango del arreglo del gato.
            if(strcmp(instructionsArray[i].name,"addi") == 0){
                //Se verifica si el immediate de la instruccion esta dentro del rango valido.
                if((instructionsArray[i].immediate >= 0) && (instructionsArray[i].immediate <= 9)){
                    //Se verifica si el tablero en la posicion esta vacio (V).
                    if(strcmp(ticTacToe->board[instructionsArray[i].immediate - 1],"V") == 0){
                        //Como se pasan todas las verificaciones, se procede a realizar la jugada.
                        strcpy(ticTacToe->board[instructionsArray[i].immediate - 1],instructionsArray[i].rt);
                        //Pregunta si un jugador a ganado y si es que ya ha impreso la jugada ganadora.
                        if(aux == 0  && verifyWinner(ticTacToe)){
                            showBoard(ticTacToe);
                            //Validaciones para saber que jugador gano en que turno e informarle al usuario.
                            if(strcmp(instructionsArray[i].rt,ticTacToe->playerX) == 0){
                                printf("Gano el jugador X en el turno %d\n\n", i - 1);
                            }
                            else{
                                printf("Gano el jugador O en el turno %d\n\n", i - 1);
                            }
                            //Se actualizan variables auxiliares para el funcionamiento de procesamientos.
                            //Si boolAux2 es true, indica que existe un ganador en el juego.
                            boolAux2 = true;
                            //Aux es una variable que indica si ya se ha mostrado por pantalla el tablero donde gana un jugador.
                            aux = -1;
                        }
                    }
                    else{
                        //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                        printf("ERROR : TRATA DE SOBREESCRIBIR UNA JUGADA... Instruccion %d\n\n",i + 1);
                    }
                }
                    else{
                        //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                        printf("ERROR : INSTRUCCION ADDI CON IMMEDIATE FUERA DE RANGO... Instruccion %d.\n\n",i + 1);
                    }
                    //Actualizacion contadores PipeLine
                    pipeLine = updatePipeLine(pipeLine,instructionsArray[i].name);
                }
            //En este caso, como el tablero no fue creado por instruccion mips, la instruccion sw no puede ser ejecutada.
            else{
                //Se verifica si el immediate de la instruccion esta dentro del rango valido.
                if((instructionsArray[i].immediate >= 0) && (instructionsArray[i].immediate <= 9)){
                    //Se verifica si en la posicion en la cual se quiere borrar una jugada, corresponde a un movimiento anterior del mismo jugador.
                    if(strcmp(ticTacToe->board[instructionsArray[i].immediate - 1],instructionsArray[i].rt) == 0){
                        //En caso de que es el mismo jugador, se procede a eliminar dicha jugada.
                        strcpy(ticTacToe->board[instructionsArray[i].immediate - 1],"V");
                    }
                    else{
                        //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                        printf("ERROR : TRATA DE ELIMINAR JUGADA QUE NO LE PERTENECE O NO EXISTE... Instruccion %d\n\n",i + 1);
                    }
                }
                else{
                    //Se envia un mensaje al usuario indicando que numero de jugada no es valida.
                    printf("ERROR : INSTRUCCION SUBI CON IMMEDIATE FUERA DE RANGO... Instruccion %d.\n\n",i + 1);
                }
                //Actualizacion contadores PipeLine
                pipeLine = updatePipeLine(pipeLine,instructionsArray[i].name);
            }
        }
    }
    //Se imprime el tablero final.
    printf("EL TABLERO FINAL ES:\n\n");
    showBoard(ticTacToe);
    //Se pregunta si no hubo ningun ganador.
    if(boolAux2 == false){
        printf("EL TABLERO ESTA INCOMPLETO O LOS JUGADORES EMPATARON\n\n");
    }
    //Se imprime el PipeLine.
    printf("EL PIPELINE ES:\n\n");
    showPipeLine(pipeLine);

    return ticTacToe;
}

//Procedimiento auxiliar para ordenar el uso de los distintos procedimientos.
//Entrada: Char* que representa el nombre del archivo que contiene las jugadas.
//Salida: Vacia.
void game(char* fileName){
    int instructionLines = 0;
    instructionLines = readLines(fileName);
    Instruction* instructions = (Instruction*)malloc(sizeof(Instruction) * instructionLines);
    instructions = readInstructions(fileName, instructionLines,instructions);
    TicTacToe* ticTacToe = (TicTacToe*)malloc(sizeof(TicTacToe));
    PipeLine* pipeLine = (PipeLine*)malloc(sizeof(PipeLine));
    ticTacToe = playTicTacToe(instructions,ticTacToe,pipeLine,instructionLines);

}

//Procedimiento que muestra la usuario las opciones que posee al momento de iniciar el programa.
//Entrada: Vacia.
//Salida: Vacia
void menu(){
    char* option = (char*)malloc(sizeof(char)* OPTION);
    char* fileName = (char*)malloc(sizeof(char) * NAME_FILE);

    while(true){
        printf("\nSeleccione una opción...\n");
        printf("1- Ingresar nombre de archivo con las jugadas.\n");
        printf("2- Salir del programa.\n");
        printf("Opcion: ");
        scanf("%s",option);
        if(strcmp("1",option) == 0){
            printf("Ingrese el nombre de archivo de texto: ");
            scanf("%s",fileName);
            game(fileName);
        }
        else if(strcmp("2",option) == 0){
            printf("\nCerrando...\n");
            free(option);
            free(fileName);
            break;
        }
        else{
            printf("\nIngrese una opcion valida.\n\n");
        }
    }
}

//Procedimiento Main que da el inicio al programa.
//Entrada: Vacia.
//Salida: Int 0 que representa que se termino la ejecucion del programa.
int main(){
    menu();
    printf("\n");
    return 0;
}