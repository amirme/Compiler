#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>

static int lbl;

void basicInstructions(char instruction){
	if(instruction == '+'){
		printf("\tpopq\t%%rax\n");
		printf("\tpopq\t%%rbx\n");
		printf("\taddq\t%%rbx , %%rax\n");
		printf("\tpushq\t%%rax\n");
	}
	else if (instruction == '-') {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tsubq\t%%rbx , %%rax\n");
		printf("\tpushq\t%%rax\n");
	}
	else if (instruction == '*') {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\timulq\t%%rbx , %%rax\n");
		printf("\tpushq\t%%rax\n");
	}
	else if (instruction == '/'){
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tcqto\n");
		printf("\tidivq\t%%rbx , %%rax\n");
		printf("\tpushq\t%%rax\n");
	}
}

void conditionalInstruction(char *instruction){
	if (strcmp(instruction,"<") == 0) {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tcmp\t%%rbx,%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetl\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
	}
	else if (strcmp(instruction,">") == 0) {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tcmp\t%%rbx,%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetg\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
	}
	else if (strcmp(instruction,"GE") == 0) {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetge\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
	}
	else if (strcmp(instruction,"LE") == 0) {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetle\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
	}
	else if (strcmp(instruction,"NE") == 0) {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tmovq\t$1, %%r8\n");
		printf("\tmovq\t$0, %%r9\n");
		printf("\tcmpq\t%%rbx, %%rax \n");
		printf("\tcmoveq\t%%r8, %%r9\n");
	}
	else if (strcmp(instruction,"EQ") == 0) {
		printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\txor\t%%rcx, %%rcx\n");
		printf("\tsete\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
	}
}

int ex(nodeType *p) {
								int lbl1, lbl2;

								if (!p) return 0;
								switch(p->type) {
								case typeCon:

																printf("\tpushq\t$%d\n", p->con.value);
																break;
								case typeId:

																printf("\tpushq\t%c(%%rip)\n", p->id.i + 'a');
																break;
								case typeOpr:
																switch(p->opr.oper) {
																case WHILE:
																								printf("L%03d:\n", lbl1 = lbl++);
																								ex(p->opr.op[0]);
																								printf("\tjz\tL%03d\n", lbl2 = lbl++);
																								ex(p->opr.op[1]);
																								printf("\tjmp\tL%03d\n", lbl1);
																								printf("L%03d:\n", lbl2);
																								break;
																case IF:
																								ex(p->opr.op[0]);
																								if (p->opr.nops > 2) {
																																/* if else */
																																printf("\tjz\tL%03d\n", lbl1 = lbl++);
																																ex(p->opr.op[1]);
																																printf("\tjmp\tL%03d\n", lbl2 = lbl++);
																																printf("L%03d:\n", lbl1);
																																ex(p->opr.op[2]);
																																printf("L%03d:\n", lbl2);
																								} else {
																																/* if */
																																printf("\tjz\tL%03d\n", lbl1 = lbl++);
																																ex(p->opr.op[1]);
																																printf("L%03d:\n", lbl1);
																								}
																								break;
																case PRINT:
																								ex(p->opr.op[0]);
																            		printf("\n\tpopq\t%%rax\n");
																            		printf("\tpushq\t%%rdi\n");
																            		printf("\tpushq\t%%rsi\n");
																            		printf("\tmovq\t$format, %%rdi\n");
																            		printf("\tmovq\t%%rax, %%rsi\n");
																            		printf("\txor\t%%rax, %%rax\n");
																            		printf("\tcall\tprintf\n");
																            		printf("\tpopq\t%%rsi\n");
																            		printf("\tpopq\t%%rdi\n");
																								break;
																case '=':
																								ex(p->opr.op[1]);
																								printf("\tpopq\t%c(%%rip)\n", p->opr.op[0]->id.i + 'a');
																								break;
																case UMINUS:
																								ex(p->opr.op[0]);
																								printf("\n\tpopq\t%%rax\n");
																							  printf("\tnegq\t%%rax\n");
																								printf("\tpushq\t%%rax\n");
																								break;
																case FACT:
																								ex(p->opr.op[0]);
																								printf("\n\tpopq\t%%rdi\n");
																								printf("\tcall\tfactorial\n");
																								printf("\tpushq\t%%rax\n");
																								break;
																case LNTWO:
																								ex(p->opr.op[0]);
																								printf("\tlntwo\n");
																								break;
																default:
																											ex(p->opr.op[0]);
																											ex(p->opr.op[1]);
																											switch(p->opr.oper) {
																											case GCD:   printf("\tgcd\n");
																											break;
																								case '+':
																											basicInstructions('+');
																								 			break;
																								case '-':
																											basicInstructions('-');
																											break;
																								case '*':
																											basicInstructions('*');
																											break;
																								case '/':
																											basicInstructions('/');
																											break;
																								case '<':
																											conditionalInstruction("<");
																											break;
																								case '>':
																											conditionalInstruction(">");
																											break;
																								case GE:
																											conditionalInstruction("GE");
																											break;
																								case LE:
																											conditionalInstruction("LE");
																											break;
																								case NE:
																											conditionalInstruction("NE");
																											break;
																								case EQ:
																											conditionalInstruction("EQ");
																											break;
																								}
																}
								}
								return 0;
}

//printf("\tadd\n");
