//Liberias utilizadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Variables definidas.
#define WORD 10
#define OPTION 10
#define NAME_FILE 20
#define BOARD_LENGTH 9

//Structs utilizados.
typedef struct{
    char* name;
    char* rt;
    char* rs;
    int offset;
    int immediate;
}Instruction;

typedef struct{
    char* playerX;
    char* playerO;
    char* boardRegister;
    char** board;
}TicTacToe;

typedef struct{
    int IF;
    int ID;
    int EX;
    int MEM;
    int WB;
}PipeLine;

//Procedimientos definidos.
int readLines(char* fileName);
void showBoard(TicTacToe* ticTacToe);
bool verifyWinner(TicTacToe* ticTacToe);
PipeLine* updatePipeLine(PipeLine* pipeLine,char* instructionName);
void showPipeLine(PipeLine* pipeLine);
char* getInstructionName(char* instruction);
char* getInstructionRT(char* instruction);
char* getInstructionRS(char* instruction);
int getInstructionImmediate(char* instruction);
int getInstructionOffset(char* instruction);
Instruction* readInstructions(char* fileName, int lengthInstructions,Instruction* instructionList);
TicTacToe* playTicTacToe(Instruction* instructionsArray,TicTacToe* ticTacToe,PipeLine* pipeLine,int lengthInstructions);
void game(char* fileName);
void menu();