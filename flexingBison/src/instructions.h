
#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#define ADD()       printf("\tADD\n");
#define SUB()       printf("\tSUB\n");
#define MULT()      printf("\tMULT\n");
#define DIV()       printf("\tDIV\n");
#define MOD()       printf("\tMOD\n");
#define AND()       printf("\tAND\n");
#define OR()        printf("\tOR\n");
#define NEG()       printf("\tNEG\n");
#define NOT()       printf("\tNOT\n");
#define EQ()       printf("\tEQ\n");
#define NE()       printf("\tNE\n");
#define LT()        printf("\tLT\n");
#define LE()        printf("\tLE\n");
#define GT()        printf("\tGT\n");
#define GE()        printf("\tGE\n");
#define IN()        printf("\tIN\n");
#define OUT()       printf("\tOUT\n");
#define NOP()       printf("\tNOP\n");
#define LDC(I)      printf("\tLDC %d\n", I);
#define LDA(I,J)    printf("\tLDA %d %d\n", I, J);
#define LDV(I, J)   printf("\tLDV %d %d\n", I, J);
#define LDI(I, J)   printf("\tLDI %d %d\n", I, J);
#define ST(I, J)    printf("\tST %d %d\n", I, J);
#define STI(I, J)   printf("\tSTI %d %d\n", I, J);
#define JMP(I)      printf("\tJMP L%d\n", I);
#define JMPF(I)     printf("\tJMPF L%d\n", I);
#define JMPT(I)     printf("\tJMPT L%d\n", I);
#define INIT()      printf("\tINIT\n");
#define HALT()      printf("\tHALT\n");
#define ALLOC(I)    printf("\tALLOC %d\n",I);
#define CALL(I)     printf("\tCALL L%d\n",I);
#define PROC(I)     printf("\tPROC %d\n",I);
#define RET(I)      printf("\tRET %d\n",I);
#define ENTER(I)    printf("\tENTER %d\n",I);
#define EXIT(I)     printf("\tEXIT %d\n",I);
#define DUP()       printf("\tDUP\n");
#define POP()       printf("\tPOP %d\n");
#define STL()       printf("\tSTL\n");
#define IND()       printf("\tIND\n");
#define INCH()      printf("\tINCH\n");
#define OUTCH()     printf("\tOUTCH\n");
#define OUTSTR(I)   printf("\tALLOC %d\n",I);
#define LABEL(L)    printf("L%d\tNOP\n", L);

#endif