//Liberias utilizadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Variables definidas.
#define WORD 10
#define OPTION 10
#define NAME_FILE 20
#define A_REGISTER_QUANTITY 4
#define T_REGISTER_QUANTITY 10
#define V_REGISTER_QUANTITY 2
#define S_REGISTER_QUANTITY 8
#define K_REGISTER_QUANTITY 2
#define CC_SIZE 100

//Structs utilizados.

typedef struct Instruction{
    char* name; // En caso de ser un Label este campo tendra el nombre del label.
    char type; // Se agrega el tipo L en caso de ser un label.
    char* rs;
    char* rt;
    char* rd;
    int immediate;
    int offset;
    char* address;
}Instruction;

typedef struct RegisterList{
	int $zero;
    int $a[A_REGISTER_QUANTITY];
	int $t[T_REGISTER_QUANTITY];
    int $v[V_REGISTER_QUANTITY];
    int $s[S_REGISTER_QUANTITY];
    int $k[K_REGISTER_QUANTITY];
	int $sp;
    int $ra;
}RegisterList;

//ACUERDATE DE PENSAR SI ES NECESARIO STRUCT BUFFER
//Y SI SON NECESARIOS, COMO HACERLOS.
//ANIMO JAVIER DEL FUTURO.

//Procedimientos definidos.
bool verifyInString(char* regCmp, char* reg);
int readLines(char* fileName);
int getSPSize(Instruction* instructionList, int instructionLines);
int getAddresIndex(Instruction* instructionList, char* address, int instructionLines);
char* getInstructionName(char* instruction);
char getInstructionType(char* instruction);
char* getInstructionRT(char* instruction);
char* getInstructionRS(char* instruction);
char* getInstructionRD(char* instruction);
int getInstructionImmediate(char* instruction);
int getInstructionOffset(char* instruction);
char* getInstructionAddress(char* instruction);
Instruction* readInstructions(char* fileName, int quantityInstructions,Instruction* instructionList); //
RegisterList setRegisterValue(RegisterList registers,char* reg,int value); 
int getRegisterValue(RegisterList registers,char* reg);
RegisterList initializeRegister(RegisterList registers);
void initializeSPArray(int* SPArray, int sizeArray);
bool verifyDataHazardType1(Instruction* instructionList, Instruction instruction, int aux,FILE* fileHazard, FILE* fileHazardSolution, int count); //
bool verifyDataHazardType2(Instruction* instructionList, Instruction instruction, int aux,FILE* fileHazard, FILE* fileHazardSolution, int count); //
bool verifyControlHazard(Instruction instruction, int aux, FILE* fileHazard, FILE* fileHazardSolution, int count); //
RegisterList processor(RegisterList registers, Instruction* instructionList, int instructionLines, int* SPArray); //
void printRegisters(RegisterList registers, int* arraySP, Instruction* instructionList, int instructionLines);
void begin(char* fileName);
void menu(); // 