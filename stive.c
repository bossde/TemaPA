#include "header.h"

Team* top(StackNode *top){
	if (isEmptyStack(top)) return NULL;
	return top->StackTeam;
} 

void push(StackNode**top, Team* v) {
	StackNode* newNode=(StackNode*)malloc(sizeof(StackNode));
	newNode->StackTeam=v;
	newNode->next=*top;
	*top=newNode;
}

Team* pop(StackNode**top) {
	if (isEmptyStack(*top)) return NULL;
	StackNode *temp=(*top); 		
	Team* aux=temp->StackTeam;	
	*top=(*top)->next;      		
	free(temp);
	return aux;
}

int isEmptyStack(StackNode*top){
	return top==NULL;
}
	
void deleteStack(StackNode**top){
	StackNode *temp;
	while (!isEmptyStack(*top)){
		temp=*top;
		*top=(*top)->next;
		free(temp);
    }
}

void PrintStack(StackNode**top, FILE* output){
    Team* output_team = NULL;
        while(*top){
            output_team = pop(top);
            fprintf(output,"%s %.2f\n",output_team->name, output_team->team_points);
        }
		fprintf(output,"\n");
}