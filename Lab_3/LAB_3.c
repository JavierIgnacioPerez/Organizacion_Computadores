#include "LAB_3.h"

//Procedimiento que dado un Char* y  otro Char*, revisa si el primero esta contenido en el segundo.
//Entrada: Char* regCmp, Char* reg.
//Salida: Boolean True si regCMp esta contenido en reg, False en caso contrario.
bool verifyInString(char* regCmp, char* reg){
    if(regCmp[1] == reg[1]){
        return true;
    }
    return false;
} 

//Procedimiento que permite leer el archivo de entrada y retorna la cantidad de lineas que este contiene.
//Entrada: Char* que representa el nombre del archivo a leer.
//Salida: Int que representa la cantidad de lineas que posee el archivo de texto.
int readLines(char* fileName){
    FILE* file;
    int count = 0;
    char wordAux[50];
    file = fopen(fileName,"r");
    if(file == NULL){
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

//Procedimiento que dado Struct Instruction*, encuentra la instrucción que genera el arreglo en $sp y retorna dicho numero.
//Entrada: Struct Instruction* que representa el conjunto de instrucciones.
//Salida: Int que representa el tamaño del arreglo donde se reserva memoria.
int getSPSize(Instruction* instructionList, int instructionLines){

    for(int i = 0; i < instructionLines; i++){
        if( strcmp(instructionList[i].name,"addi") == 0){
            if( strcmp(instructionList[i].rd,"$sp") == 0 || strcmp(instructionList[i].rs,"$sp") == 0){
                return -1 * instructionList[i].immediate;
            }
        }
    }
    return 0;
}

//Procedimiento que dado un Char*, busca en el struct Instruction* dicho address y retorna el indice de dicho address.
//Entrada: Struct Instruction y Char* que es el address a buscar.
//Salida: integer que representa el indice donde se encuentra dicho address.
int getAddresIndex(Instruction* instructionList, char* address, int instructionLines){
    for(int i = 0; i < instructionLines; i++){
        if(strcmp(instructionList[i].name,address) == 0  && instructionList[i].type == 'l'){
            return i;
        }
    }
    return -1;
}

//Procedimiento que dado una instruccion MIPS, retorna el nombre de la instrucción MIPS
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Char* que representa el nombre de la instruccion MIPS.
char* getInstructionName(char* instruction){
    char* auxStr = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    auxStr = strtok(instructionAux," ,:");
    return auxStr;
}

//Procedimiento que dado una instruccion MIPS, retorna el tipo de la instruccion (L en caso de label)
//Entrada: Char* name, que representa la instruccion MIPS.
//Salida: Char que representa el tipo de la instruccion MIPS.
char getInstructionType(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if((strcmp(name,"add") == 0) || (strcmp(name,"sub") == 0) ||  (strcmp(name,"div") == 0) ||  (strcmp(name,"mult") == 0)){
        return 'r';
    }
    else if((strcmp(name,"addi") == 0) || (strcmp(name,"addiu") == 0) || (strcmp(name,"subi") == 0) ||
            (strcmp(name,"bgt") == 0) || (strcmp(name,"beq") == 0) || (strcmp(name,"blt") == 0) ||  (strcmp(name,"bne") == 0) ||
            (strcmp(name,"lw") == 0) ||  (strcmp(name,"sw") == 0)){
        return 'i';
    }
    else if((strcmp(name,"j") == 0) ||  (strcmp(name,"jal") == 0) ||  (strcmp(name,"jr") == 0)){
        return 'j';
    }
    else{
        return 'l';
    }
}

//Procedimiento que dado una instruccion MIPS, retorna el registro $rt de la instrucción MIPS
//Entrada: Char* type, que representa la instruccion MIPS.
//Salida: Char* que representa el registro $rt de la instruccion MIPS.
char* getInstructionRT(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if( (strcmp(name,"add") == 0) || (strcmp(name,"sub") == 0) ||  (strcmp(name,"div") == 0) ||  (strcmp(name,"mult") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if((strcmp(name,"addi") == 0) || (strcmp(name,"addiu") == 0) || (strcmp(name,"subi") == 0) ||
            (strcmp(name,"lw") == 0) ||  (strcmp(name,"sw") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if ((strcmp(name,"bgt") == 0) || (strcmp(name,"beq") == 0) || (strcmp(name,"blt") == 0) ||  (strcmp(name,"bne") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
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

    if((strcmp(name,"add") == 0) || (strcmp(name,"sub") == 0) ||  (strcmp(name,"div") == 0) ||  (strcmp(name,"mult") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if((strcmp(name,"addi") == 0) || (strcmp(name,"addiu") == 0) || (strcmp(name,"subi") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if((strcmp(name,"lw") == 0) || (strcmp(name,"sw") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if((strcmp(name,"bgt") == 0) || (strcmp(name,"beq") == 0) || (strcmp(name,"blt") == 0) ||  (strcmp(name,"bne") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if((strcmp(name,"jr") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else{
        return "";
    }
}

//Procedimiento que dado una instruccion MIPS, retorna el registro $rs de la instrucción MIPS
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Char* que representa el registro $rd de la instruccion MIPS.
char* getInstructionRD(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if((strcmp(name,"add") == 0) || (strcmp(name,"sub") == 0) ||  (strcmp(name,"div") == 0) ||  (strcmp(name,"mult") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
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

    if((strcmp(name,"addi") == 0) || (strcmp(name,"addiu") == 0) || (strcmp(name,"subi") == 0)){
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

    if((strcmp(name,"lw") == 0) ||  (strcmp(name,"sw") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return atoi(result);
    }/*
    else if ((strcmp(name,"bgt") == 0) || (strcmp(name,"beq") == 0) || (strcmp(name,"blt") == 0) ||  (strcmp(name,"bne") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return atoi(result);
    }*/
    else{
        return 0;
    }    

}

//Procedimiento que dado una instruccion MIPS, retorna el address, si es que existe, de la instrucción MIPS. En caso de no existir retorna un string vacio
//Entrada: Char* instruction, que representa la instruccion MIPS.
//Salida: Char* que representa el address de la instruccion MIPS.
char* getInstructionAddress(char* instruction){
    char* name = (char*)malloc(sizeof(char) * WORD);
    char* result = (char*)malloc(sizeof(char) * WORD);
    char* instructionAux = (char*)malloc(sizeof(char) * WORD);
    strcpy(instructionAux,instruction);
    name = getInstructionName(instructionAux);

    if((strcmp(name,"j") == 0) ||  (strcmp(name,"jal") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else if ((strcmp(name,"bgt") == 0) || (strcmp(name,"beq") == 0) || (strcmp(name,"blt") == 0) ||  (strcmp(name,"bne") == 0)){
        result = strtok(instructionAux," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        result = strtok(NULL," ,():");
        return result;
    }
    else{
        return "";
    }
}

//Procedimiento que dado un Struct Instruction, lee el archivo y por cada linea (Instruccion MIPS) obtiene la informacion y la guarda dentro de las variables del Struct.
//Entrada: Char* que representa el nombre del archivo, Int que representa la cantidad de instrucciones, Struct Instruction que representa el struct donde se guardad la informacion.
//Salida: Un arreglo de Struct Instruction, que contiene, por cada posicion, la informacion de cada instruccion MIPS.
Instruction* readInstructions(char* fileName, int quantityInstructions,Instruction* instructionList){
    FILE* file;
    char wordAux[50];
    int i;

    for(int i = 0; i < quantityInstructions; i++){
        instructionList[i].name = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].rs = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].rt = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].rd = (char*)malloc(sizeof(char) * WORD);
        instructionList[i].address = (char*)malloc(sizeof(char) * WORD);
    }

    file = fopen(fileName,"r");
    if(file == NULL){
        printf("\nEl archivo no existe...\n");
        return instructionList;
    }
    else{
        i = 0;
        while(!feof(file)){
            fscanf(file," %[^\n]",wordAux);

            strcpy(instructionList[i].name,getInstructionName(wordAux)); 
            instructionList[i].type = getInstructionType(wordAux); 
            strcpy(instructionList[i].rs,getInstructionRS(wordAux));
            strcpy(instructionList[i].rt,getInstructionRT(wordAux));
            strcpy(instructionList[i].rd,getInstructionRD(wordAux));
            instructionList[i].immediate = getInstructionImmediate(wordAux);
            instructionList[i].offset = getInstructionOffset(wordAux);
            strcpy(instructionList[i].address,getInstructionAddress(wordAux));

            i += 1;
            }
        }  
    fclose(file);
    return instructionList;
}

//Procedimiento que dado un Struc RegisterList,un Char* que representa el registro y un Char* que representa al offset,
//obtiene el valor de este dentro de la estructura.
//Entrada: Struct RegisterList,Char* reg y Int offset.
//Salida: Int que representa el valor contenido en dicho registro.
int getRegisterValue(RegisterList registers,char* reg){
    char* result = (char*)malloc(sizeof(char) * WORD);
    char wordAux[50];

    if(strcmp("$zero",reg) == 0){
        return registers.$zero;
    }
    else if (strcmp("$sp",reg) == 0){
        return registers.$sp;
    }
    else if (strcmp("$ra",reg) == 0){
        return registers.$ra;
    }
    else if(verifyInString("$a",reg)){
        result = strtok(reg,"$a");
        return registers.$a[atoi(result)];
    }
    else if(verifyInString("$t",reg)){
        result = strtok(reg,"$t");
        return registers.$t[atoi(result)];
    }
    else if(verifyInString("$v",reg)){
        result = strtok(reg,"$v");
        return registers.$v[atoi(result)];
    }
    else if(verifyInString("$s",reg)){
        result = strtok(reg,"$s");
        return registers.$s[atoi(result)];
    }
    else if(verifyInString("$k",reg)){
        result = strtok(reg,"$k");
        return registers.$k[atoi(result)];
    }
    else{
        return -1;
    }
}

//Procedimiento que dado un Struc RegisterList,un Char* que representa el registro y un Char* que representa al offset,
//modifica el valor de este dentro de la estructura.
//Entrada: Struct RegisterList y Char* reg.
//Salida: Struct RegisterList actualizado.
RegisterList setRegisterValue(RegisterList registers,char* reg,int value){
    char* result = (char*)malloc(sizeof(char) * WORD);
    char wordAux[50];

    if(strcmp("$sp",reg) == 0){
        registers.$sp = value;
        return registers;
    }
    else if (strcmp("$ra",reg) == 0){
        registers.$ra = value;
        return registers;
    }
    else if(verifyInString("$a",reg)){
        result = strtok(reg,"$a");
        registers.$a[atoi(result)] = value;
        return registers;
    }
    else if(verifyInString("$t",reg)){
        result = strtok(reg,"$t");
        registers.$t[atoi(result)] = value;
        return registers;
    }
    else if(verifyInString("$v",reg)){
        result = strtok(reg,"$v");
        registers.$v[atoi(result)] = value;
        return registers;
    }
    else if(verifyInString("$s",reg)){
        result = strtok(reg,"$s");
        registers.$s[atoi(result)] = value;
        return registers;
    }
    else if(verifyInString("$k",reg)){
        result = strtok(reg,"$k");
        registers.$k[atoi(result)] = value;
        return registers;
    }
    else{
        return registers;
    }
}

//Procedimiento que dado un Struct RegisterList, inicializa en cero todas las variables de dicho Struct.
//Entrada: Struct RegisterList.
//Salida: Struct RegisterList inicializados.
RegisterList initializeRegister(RegisterList registers){
    
	registers.$zero = 0;
    for(int i = 0; i < A_REGISTER_QUANTITY; i++){
        registers.$a[i] = 0;
    }
    for(int i = 0; i < T_REGISTER_QUANTITY; i++){
        registers.$t[i] = 0;
    }
    for(int i = 0; i < V_REGISTER_QUANTITY; i++){
        registers.$v[i] = 0;
    }
    for(int i = 0; i < S_REGISTER_QUANTITY; i++){
        registers.$s[i] = 0;
    }
    for(int i = 0; i < K_REGISTER_QUANTITY; i++){
        registers.$k[i] = 0;
    }
    registers.$sp = 200000;
    registers.$ra = 0;

    return registers;
}

//Procedimiento que dado un array de integer SPArray, inicializa en -1 todas las variables de dicho Struct.
//Entrada: Int* SPArray
//Salida: No posee salida.
void initializeSPArray(int* SPArray, int sizeArray){

    for(int i = 0; i < sizeArray; i++){
        SPArray[i] = -1;
    }
}

//Procedimiento que dado una instruccion y el Struct Instruction*, detecta si existe un hazard de datos de tipo 1.
//Entrada: Struct Instruction*, Instruction instruction y la cantidad de instrucciones.
//Salida: True si existe un hazard de datos de tipo 1, False en caso contrario
bool verifyDataHazardType1(Instruction* instructionList, Instruction instruction, int aux,FILE* fileHazard,FILE* fileHazardSolution,int count){
    
    char* auxS = (char*)malloc(sizeof(char) * 25);

    if( strcmp(instructionList[aux - 1].name,"add") == 0 || strcmp(instructionList[aux - 1].name,"sub") == 0 || strcmp(instructionList[aux - 1].name,"mult") == 0 || strcmp(instructionList[aux - 1].name,"div") == 0){
        if (strcmp(instructionList[aux - 1].rd, instruction.rd) == 0 || strcmp(instructionList[aux - 1].rd, instruction.rs) == 0 || strcmp(instructionList[aux - 1].rd, instruction.rt) == 0 ){
            
            sprintf(auxS, "%d", count);
            fputs(auxS,fileHazard);
            fputs(auxS,fileHazardSolution);
            fputs(".- HAZARD DE DATOS TIPO 1 ENTRE ",fileHazard);
            fputs(instructionList[aux - 1].name,fileHazard);
            fputs(" ",fileHazard);
            fputs("Y",fileHazard);
            fputs(" ",fileHazard);
            fputs(instruction.name,fileHazard);
            fputs(" EN INSTRUCCION ",fileHazard);
            sprintf(auxS, "%d", aux + 1);
            fputs(auxS,fileHazard);
            fputs("\n",fileHazard);

            fputs(".- SE SOLUCIONA CON FORWARDING DE EX/MEM A ID/EX\n",fileHazardSolution);

            return true;
        }
        return false;
    }
    else if ( strcmp(instructionList[aux - 1].name,"addi") == 0 || strcmp(instructionList[aux - 1].name,"addiu") == 0 || strcmp(instructionList[aux - 1].name,"subi") == 0){
        if (strcmp(instructionList[aux - 1].rt, instruction.rd) == 0 || strcmp(instructionList[aux - 1].rt, instruction.rs) == 0 || strcmp(instructionList[aux - 1].rt, instruction.rt) == 0 ){
            
            sprintf(auxS, "%d", count);
            fputs(auxS,fileHazard);
            fputs(auxS,fileHazardSolution);
            fputs(".- HAZARD DE DATOS TIPO 1 ENTRE ",fileHazard);
            fputs(instructionList[aux - 1].name,fileHazard);
            fputs(" ",fileHazard);
            fputs("Y",fileHazard);
            fputs(" ",fileHazard);
            fputs(instruction.name,fileHazard);
            fputs(" EN INSTRUCCION ",fileHazard);
            sprintf(auxS, "%d", aux + 1);
            fputs(auxS,fileHazard);
            fputs("\n",fileHazard);

            fputs(".- SE SOLUCIONA CON FORWARDING DE EX/MEM A ID/EX\n",fileHazardSolution);

            return true;
        }
        return false;
    }
    else if (strcmp(instructionList[aux - 1].name,"lw") == 0){
        if (strcmp(instructionList[aux - 1].rt, instruction.rd) == 0 || strcmp(instructionList[aux - 1].rt, instruction.rs) == 0 || strcmp(instructionList[aux - 1].rt, instruction.rt) == 0 ){
            
            sprintf(auxS, "%d", count);
            fputs(auxS,fileHazard);
            fputs(auxS,fileHazardSolution);
            fputs(".- HAZARD DE DATOS TIPO 1 ENTRE ",fileHazard);
            fputs(instructionList[aux - 1].name,fileHazard);
            fputs(" ",fileHazard);
            fputs("Y",fileHazard);
            fputs(" ",fileHazard);
            fputs(instruction.name,fileHazard);
            fputs(" EN INSTRUCCION ",fileHazard);
            sprintf(auxS, "%d", aux + 1);
            fputs(auxS,fileHazard);
            fputs("\n",fileHazard);

            fputs(".- SE SOLUCIONA CON FORWARDING DE MEM/WB A ID/EX\n",fileHazardSolution);

            return true;
        }
        return false;
    }
    return false;
}

//Procedimiento que dado una instruccion y el Struct Instruction*, detecta si existe un hazard de datos de tipo 2.
//Entrada: Struct Instruction*, Instruction instruction y la cantidad de instrucciones.
//Salida: True si existe un hazard de datos de tipo 2, False en caso contrario
bool verifyDataHazardType2(Instruction* instructionList, Instruction instruction, int aux,FILE* fileHazard,FILE* fileHazardSolution,int count){
        
    char* auxS = (char*)malloc(sizeof(char) * 25);

    if( strcmp(instructionList[aux - 2].name,"add") == 0 || strcmp(instructionList[aux - 2].name,"sub") == 0 || strcmp(instructionList[aux - 2].name,"mult") == 0 || strcmp(instructionList[aux - 2].name,"div") == 0){
        if (strcmp(instructionList[aux - 2].rd, instruction.rd) == 0 || strcmp(instructionList[aux - 2].rd, instruction.rs) == 0 || strcmp(instructionList[aux - 2].rd, instruction.rt) == 0 ){
            
            sprintf(auxS, "%d", count);
            fputs(auxS,fileHazard);
            fputs(auxS,fileHazardSolution);
            fputs(".- HAZARD DE DATOS TIPO 2 ENTRE ",fileHazard);
            fputs(instructionList[aux - 1].name,fileHazard);
            fputs(" ",fileHazard);
            fputs("Y",fileHazard);
            fputs(" ",fileHazard);
            fputs(instruction.name,fileHazard);
            fputs(" EN INSTRUCCION ",fileHazard);
            sprintf(auxS, "%d", aux + 1);
            fputs(auxS,fileHazard);
            fputs("\n",fileHazard);

            fputs(".- SE SOLUCIONA CON FORWARDING DE MEM/WB A ID/EX\n",fileHazardSolution);

            return true;
        }
        return false;
    }
    else if ( strcmp(instructionList[aux - 2].name,"addi") == 0 || strcmp(instructionList[aux - 2].name,"addiu") == 0 || strcmp(instructionList[aux - 2].name,"subi") == 0){
        if (strcmp(instructionList[aux - 2].rt, instruction.rd) == 0 || strcmp(instructionList[aux - 2].rt, instruction.rs) == 0 || strcmp(instructionList[aux - 2].rt, instruction.rt) == 0 ){
            
            sprintf(auxS, "%d", count);
            fputs(auxS,fileHazard);
            fputs(auxS,fileHazardSolution);
            fputs(".- HAZARD DE DATOS TIPO 2 ENTRE ",fileHazard);
            fputs(instructionList[aux - 1].name,fileHazard);
            fputs(" ",fileHazard);
            fputs("Y",fileHazard);
            fputs(" ",fileHazard);
            fputs(instruction.name,fileHazard);
            fputs(" EN INSTRUCCION ",fileHazard);
            sprintf(auxS, "%d", aux + 1);
            fputs(auxS,fileHazard);
            fputs("\n",fileHazard);

            fputs(".- SE SOLUCIONA CON FORWARDING DE MEM/WB A ID/EX\n",fileHazardSolution);

            return true;
        }
        return false;
    }
    else if ((strcmp(instructionList[aux - 2].name,"lw") == 0)){
        if (strcmp(instructionList[aux - 2].rt, instruction.rd) == 0 || strcmp(instructionList[aux - 2].rt, instruction.rs) == 0 || strcmp(instructionList[aux - 2].rt, instruction.rt) == 0 ){
            
            sprintf(auxS, "%d", count);
            fputs(auxS,fileHazard);
            fputs(auxS,fileHazardSolution);
            fputs(".- HAZARD DE DATOS TIPO 2 ENTRE ",fileHazard);
            fputs(instructionList[aux - 1].name,fileHazard);
            fputs(" ",fileHazard);
            fputs("Y",fileHazard);
            fputs(" ",fileHazard);
            fputs(instruction.name,fileHazard);
            fputs(" EN INSTRUCCION ",fileHazard);
            sprintf(auxS, "%d", aux + 1);
            fputs(auxS,fileHazard);
            fputs("\n",fileHazard);

            fputs(".- SE SOLUCIONA CON FORWARDING DE MEM/WB A ID/EX\n",fileHazardSolution);

            return true;
        }
        return false;
    }
    else{
        return false;
    }
}

//Procedimiento que dado una instruccion y el Struct Instruction*, detecta si existe un hazard de control.
//Entrada: Struct Instruction*, Instruction instruction y la cantidad de instrucciones.
//Salida: True si existe un hazard de control, False en caso contrario
//--------------------------------------------BRANCH NOT TAKEN--------------------------------------------
bool verifyControlHazard(Instruction instruction, int aux,FILE* fileHazard,FILE* fileHazardSolution,int count){
    
    char* auxS = (char*)malloc(sizeof(char) * 25);

    if(strcmp(instruction.name,"beq") == 0 || strcmp(instruction.name,"bgt") == 0 || strcmp(instruction.name,"blt") == 0 ||
    strcmp(instruction.name,"bne") == 0){
        //SON TRES NOP PORQUE EL SALTO SE HACEN EN EX/MEM.

        sprintf(auxS, "%d", count);
        fputs(auxS,fileHazard);
        fputs(auxS,fileHazardSolution);
        fputs(".- HAZARD DE CONTROL EN ",fileHazard);
        fputs(instruction.name,fileHazard);
        fputs(" EN INSTRUCCION ",fileHazard);
        sprintf(auxS, "%d", aux + 1);
        fputs(auxS,fileHazard);
        fputs("\n",fileHazard);

        fputs(".- SE SOLUCIONA CON TRES NOP EN IF/ID, ID/EX Y EX/MEM\n",fileHazardSolution);

        return true;
    }
    else if(strcmp(instruction.name,"j") == 0|| strcmp(instruction.name,"jal") == 0 || strcmp(instruction.name,"jr") == 0){
        //ES SOLO UN NOP PORQUE SALTA EN EL BUFER IF/ID.

        sprintf(auxS, "%d", count);
        fputs(auxS,fileHazard);
        fputs(auxS,fileHazardSolution);
        fputs(".- HAZARD DE CONTROL EN ",fileHazard);
        fputs(instruction.name,fileHazard);
        fputs(" EN INSTRUCCION ",fileHazard);
        sprintf(auxS, "%d", aux + 1);
        fputs(auxS,fileHazard);
        fputs("\n",fileHazard);

        fputs(".- SE SOLUCIONA CON UN NOP EN IF/ID\n",fileHazardSolution);

        return true;
    }
    return false;
}

//Procedimiento que dado un Struct RegisterList, el Struct Instruction*, la cantidad de instrucciones,
// y el arreglo que representa lo contenido en SP. ejecuta el codigo MIP
//Entrada: Struct RegisterList y Struct Instruction.
//Salida: Struct RegisterList con los valores actualizados.
RegisterList processor(RegisterList registers, Instruction* instructionList, int instructionLines, int* SPArray){

    FILE* fileHazard;
    FILE* fileHazardSolution;
    int aux = 0;
    fileHazard = fopen("Hazard.txt","wt");
    fileHazardSolution = fopen("Hazard_Solution.txt","wt");

    for(int i = 0; i < instructionLines; i++){

        if (i == 1){
            if(verifyDataHazardType1(instructionList,instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                aux += 1;
            }
        }
        if (i > 1){
            if(verifyDataHazardType1(instructionList,instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                aux += 1;
            }
            if(verifyDataHazardType2(instructionList,instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                aux += 1;
            }
        }

        if((strcmp(instructionList[i].name,"add") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rd,getRegisterValue(registers,instructionList[i].rs) + getRegisterValue(registers,instructionList[i].rt));
        }
        else if((strcmp(instructionList[i].name,"sub") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rd,getRegisterValue(registers,instructionList[i].rs) - getRegisterValue(registers,instructionList[i].rt));
        }
        else if((strcmp(instructionList[i].name,"mul") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rd,getRegisterValue(registers,instructionList[i].rs) * getRegisterValue(registers,instructionList[i].rt));
        }
        else if((strcmp(instructionList[i].name,"div") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rd,getRegisterValue(registers,instructionList[i].rs) / getRegisterValue(registers,instructionList[i].rt));
        }
        else if((strcmp(instructionList[i].name,"addi") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rt,getRegisterValue(registers,instructionList[i].rs) + instructionList[i].immediate);
        }
        else if((strcmp(instructionList[i].name,"addiu") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rt,getRegisterValue(registers,instructionList[i].rs) + instructionList[i].immediate);
        }
        else if((strcmp(instructionList[i].name,"subi") == 0)){
            registers = setRegisterValue(registers,instructionList[i].rt,getRegisterValue(registers,instructionList[i].rs) - instructionList[i].immediate);
        }
        else if(strcmp("sw",instructionList[i].name) == 0 && strcmp("$sp",instructionList[i].rs) == 0){
            SPArray[(instructionList[i].offset / 4)] = getRegisterValue(registers,instructionList[i].rt);
        }
        else if(strcmp("lw",instructionList[i].name) == 0 && strcmp("$sp",instructionList[i].rs) == 0){
            registers = setRegisterValue(registers,instructionList[i].rt,SPArray[(instructionList[i].offset / 4)]);
        }
        else if(strcmp("beq",instructionList[i].name) == 0){
            if(getRegisterValue(registers,instructionList[i].rs) == getRegisterValue(registers,instructionList[i].rt)){
                if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                    aux += 1;
                }
                i = getAddresIndex(instructionList,instructionList[i].address,instructionLines);
            }
        }
        else if(strcmp("bne",instructionList[i].name) == 0){
            if(getRegisterValue(registers,instructionList[i].rs) != getRegisterValue(registers,instructionList[i].rt)){
                if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                    aux += 1;
                }
                i = getAddresIndex(instructionList,instructionList[i].address,instructionLines);
            }
        }
        else if(strcmp("bgt",instructionList[i].name) == 0){
            if(getRegisterValue(registers,instructionList[i].rs) > getRegisterValue(registers,instructionList[i].rt)){
                if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                    aux += 1;
                }
                i = getAddresIndex(instructionList,instructionList[i].address,instructionLines);
            }
        }
        else if(strcmp("blq",instructionList[i].name) == 0){
            if(getRegisterValue(registers,instructionList[i].rs) < getRegisterValue(registers,instructionList[i].rt)){
                if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                    aux += 1;
                }
                i = getAddresIndex(instructionList,instructionList[i].address,instructionLines);
            }
        }
        else if(strcmp("j",instructionList[i].name) == 0){
            if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                aux += 1;
            }
            i = getAddresIndex(instructionList,instructionList[i].address,instructionLines);
        }
        else if(strcmp("jal",instructionList[i].name) == 0){
            if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                aux += 1;
            }
            i = getAddresIndex(instructionList,instructionList[i].address,instructionLines);
            registers.$ra = i;
        }
        else if(strcmp("jr",instructionList[i].name) == 0){
            if(verifyControlHazard(instructionList[i],i,fileHazard,fileHazardSolution,aux) == true){
                aux += 1;
            }
            i = registers.$ra;
        }
    }

    fclose(fileHazard);
    fclose(fileHazardSolution);

    return registers;
}

//Procedimiento que permite escribir en un archivo de texto los valores contenidos en cada registro.
//Entrada: Struct RegisterList.
//Salida: Vacia.
void printRegisters(RegisterList registers, int* arraySP, Instruction* instructionList, int instructionLines){
    
    FILE* fileRegister;
    fileRegister = fopen("Register.txt","wt");
    char* auxS = (char*)malloc(sizeof(char) * 25);
    sprintf(auxS, "%d", registers.$zero);
    fputs("$zero ",fileRegister);
    fputs(auxS,fileRegister);
    fputs("\n",fileRegister);
    fputs("\n",fileRegister);

    
    for(int i = 0; i < A_REGISTER_QUANTITY; i++){
        fputs("$a",fileRegister);
        sprintf(auxS, "%d", i);
        fputs(auxS,fileRegister);
        fputs(" ",fileRegister);
        sprintf(auxS, "%d", registers.$a[i]);
        fputs(auxS,fileRegister);
        fputs("\n",fileRegister);
    }
    fputs("\n",fileRegister);

    for(int i = 0; i < T_REGISTER_QUANTITY; i++){
        fputs("$t",fileRegister);
        sprintf(auxS, "%d", i);
        fputs(auxS,fileRegister);
        fputs(" ",fileRegister);
        sprintf(auxS, "%d", registers.$t[i]);
        fputs(auxS,fileRegister);
        fputs("\n",fileRegister);
    }
    fputs("\n",fileRegister);

    for(int i = 0; i < V_REGISTER_QUANTITY; i++){
        fputs("$v",fileRegister);
        sprintf(auxS, "%d", i);
        fputs(auxS,fileRegister);
        fputs(" ",fileRegister);
        sprintf(auxS, "%d", registers.$v[i]);
        fputs(auxS,fileRegister);
        fputs("\n",fileRegister);
    }
    fputs("\n",fileRegister);

    for(int i = 0; i < S_REGISTER_QUANTITY; i++){
        fputs("$s",fileRegister);
        sprintf(auxS, "%d", i);
        fputs(auxS,fileRegister);
        fputs(" ",fileRegister);
        sprintf(auxS, "%d", registers.$s[i]);
        fputs(auxS,fileRegister);
        fputs("\n",fileRegister);
    }
    fputs("\n",fileRegister);

    for(int i = 0; i < K_REGISTER_QUANTITY; i++){
        fputs("$k",fileRegister);
        sprintf(auxS, "%d", i);
        fputs(auxS,fileRegister);
        fputs(" ",fileRegister);
        sprintf(auxS, "%d", registers.$k[i]);
        fputs(auxS,fileRegister);
        fputs("\n",fileRegister);
    }

    fputs("\n",fileRegister);
    fputs("$sp",fileRegister);
    fputs(" ",fileRegister);
    sprintf(auxS, "%d", registers.$sp);
    fputs(auxS,fileRegister);
    fputs("\n",fileRegister);

    fputs("\n",fileRegister);
    fputs("$ra",fileRegister);
    fputs(" ",fileRegister);
    sprintf(auxS, "%d", registers.$ra);
    fputs(auxS,fileRegister);
    fputs("\n",fileRegister);

    fputs("\nEl contenido de SP es: ",fileRegister);
    for(int i = 0; i < getSPSize(instructionList,instructionLines); i++){
        if(arraySP[i] != -1){
            sprintf(auxS, "%d", arraySP[i]);            
            fputs(auxS,fileRegister);
            fputs(" ",fileRegister);
            
        }
    }
    fputs("\n",fileRegister);

    fclose(fileRegister);
}

//Procedimiento auxiliar para ordenar el uso de los distintos procedimientos.
//Entrada: Char* que representa el nombre del archivo que contiene las jugadas.
//Salida: Vacia.
void begin(char* fileName){
    int instructionLines = 0;
    instructionLines = readLines(fileName);
    Instruction* instructionList = (Instruction*)malloc(sizeof(Instruction) * instructionLines);
    RegisterList registers = initializeRegister(registers);
    instructionList = readInstructions(fileName,instructionLines,instructionList);
    int arraySP[getSPSize(instructionList,instructionLines)];
    initializeSPArray(arraySP,getSPSize(instructionList,instructionLines));
    registers = processor(registers,instructionList,instructionLines,arraySP);
    printRegisters(registers,arraySP,instructionList,instructionLines);
    if(instructionLines > 0){
        printf("\nSe han generado los archivos de salida exitosamente.\n");
    }

}

//Procedimiento que muestra la usuario las opciones que posee al momento de iniciar el programa.
//Entrada: Vacia.
//Salida: Vacia
void menu(){
    char* option = (char*)malloc(sizeof(char)* OPTION);
    char* fileName = (char*)malloc(sizeof(char) * NAME_FILE);

    while(true){
        printf("\nSeleccione una opción...\n");
        printf("1- Ingresar nombre de archivo con las instrucciones MIPS.\n");
        printf("2- Salir del programa.\n");
        printf("Opcion: ");
        scanf("%s",option);
        if(strcmp("1",option) == 0){
            printf("Ingrese el nombre de archivo de texto: ");
            scanf("%s",fileName);
            begin(fileName);
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