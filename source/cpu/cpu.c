#include "cpu.h"

void cpu(int32_t instructionSet[], uint16_t ip, uint16_t memorysize, uint16_t CODESIZE, uint8_t debug){
   printf("New instruction set inserted.. Size of set= %d\n", CODESIZE);
   IP = ip;
   int32_t data[CODESIZE];
   int32_t ram[CODESIZE];

   while(IP< CODESIZE){
       if(debug) printf("Instruction turn= %d | Instruction type= %s\n",IP,instructionToString(instructionSet[IP]));
      int32_t opcode=instructionSet[IP];  //fetching from the given instructionSet
     IP++;
     switch(opcode){
       case ADD:
            SP++;
            RAM[SP]=RAM[SP-1]+RAM[SP-2];  // I used a ram instead of using a subroutine. Which is a bad practice -_-
           break;
       case SUB:
            SP++;
            RAM[SP]=RAM[SP-1]-RAM[SP-2];
           break;
       case MUL:
            SP++;
            RAM[SP]=RAM[SP-1]*RAM[SP-2];
           break;
       case DIV:
            SP++;
            RAM[SP]=RAM[SP-1]/RAM[SP-2];
           break;
       case AND:
            SP++;
            RAM[SP]=RAM[SP-1]&RAM[SP-2];
           break;
       case NOT:
            SP++;
            RAM[SP]=~RAM[SP-1];
           break;
       case OR:
            SP++;
            RAM[SP]=RAM[SP-1]|RAM[SP-2];
           break;
       case XOR:
            SP++;
            RAM[SP]=RAM[SP-1]^RAM[SP-2];
           break;
       case LOAD:
            IP = instructionSet[IP];
            IP --;
           break;
       case STOR:
            SP++;
            RAM[SP] = instructionSet[IP];
           break;
       case PUSH:{
            int value=instructionSet[IP];
            IP++;
            SP++;
            RAM[SP]=value;
           break;}
       case POP:
            SP--; 
           break;
       case CALL:{
            int32_t callVALUE=instructionSet[IP];
            IP=RAM[callVALUE]; 
           break;}
       case BR:
            IP=instructionSet[IP++];
            IP--;
           break;
       case RET:
            RAM[SP]=instructionSet[IP];  
            SP++;
           break;
       case JMP:{
            IP--;  // for executing instruction at instructionSet[IP], we need to decrement IP value(because every loop turn IP value increments by 1)
           break;}
       case PRINT:{  // printing compiled data to a file
            int32_t value=RAM[SP];  // taking data from ram to disk
            if(debug) printf("Current Stack Value= %d -- Previous Stack Value= %d -- Other Previous= %d\n",value, RAM[SP-1], RAM[SP-2]);
            int x;
            for(x=0;x<=IP;x++)
                if(DATA[x]==NULL){
               DATA[x]=value;
                break;
                }
           // SP--;
           break;}
       case HALT:{
           int x;
            for(x=0;x<=IP;x++)
                 if(DATA[x]==NULL){
                DATA[x]=instructionSet[IP-1];
                break;}
            printf("CPU HALTED\n");
           return;}
            }
   }

} 
void resetcpu(){
 IP=0;
 SP=-1;
RAM[0]=NULL;
INSTRUCTIONS[0]=NULL;
DATA[0]=NULL;
}


