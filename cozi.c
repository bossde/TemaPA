#include "header.h"

Queue* createQueue(){
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	if (q == NULL) return NULL;
	q->front = q->rear=NULL;
	return q;	
}

 void enQueue(Queue*q, Team* firstTeam, Team* secondTeam){
	Match* v = (Match*) malloc(sizeof(Match));
	v->firstTeam = firstTeam;
	v->secondTeam = secondTeam;
	Element* newNode = (Element*)malloc(sizeof(Element));
	newNode->Teams = v;
	newNode->next = NULL;
	if (q->rear == NULL) q->rear = newNode; 
	else{
		(q->rear)->next = newNode;
		(q->rear) = newNode;
	}
	if (q->front == NULL) q->front = q->rear; 
}
 
Match* deQueue(Queue*q) {  
	Element* aux; Match* d;
	if (isEmpty(q)) return NULL;
	aux = q->front; 
	d = aux->Teams;
	q->front = (q->front)->next;
	free(aux);
	return d;  	
} 

int isEmpty(Queue*q){
	return (q->front == NULL);
}

void deleteQueue(Queue*q){
	Element* aux;
	while (!isEmpty(q)){
		aux = q->front;
		q->front = q->front->next;
		free(aux);
	}
	free(q);
}	

Queue* CreateQueue(Queue* q, Team* TeamList){
	while(TeamList && TeamList->nextTeam){
        enQueue(q,TeamList,TeamList->nextTeam);
        TeamList = TeamList->nextTeam->nextTeam;
    }
	return q;
}


void PrintQueue(Queue* q, FILE* output){
	Element* q_copy = q->front;
	while(q_copy != NULL){
		fprintf(output, "%s\n%s\n", q_copy->Teams->firstTeam->name,q_copy->Teams->secondTeam->name);
		q_copy = q_copy->next;
	}
	fprintf(output,"\n");
}

void PrintMatches(Queue* q, FILE* output){
	Element* q_copy = q->front;
        while(q_copy){
            fprintf(output,"%-32s - %32s\n",q_copy->Teams->firstTeam->name, q_copy->Teams->secondTeam->name);
            q_copy = q_copy->next;
        }
	fprintf(output,"\n");
}

void CalculatePoints(Queue *q){
	Element* q_copy = q->front;
	while(q_copy){
		q_copy->Teams->firstTeam->team_points = MedianCalculator(q_copy->Teams->firstTeam);
		q_copy->Teams->secondTeam->team_points = MedianCalculator(q_copy->Teams->secondTeam);
		q_copy = q_copy->next;
	}
}

void recreateQueueFromWinnersStack(Queue** q, StackNode* winnersStack) {
    while (!isEmpty(*q)) {
        deQueue(*q);
    }

    *q = createQueue();

    StackNode* winnersCopy = winnersStack;
    while (winnersCopy != NULL && winnersCopy->next != NULL) {
        enQueue(*q, winnersCopy->StackTeam,winnersCopy->next->StackTeam);
        winnersCopy = winnersCopy->next->next;
    }
}

Queue* newQueue(Queue* q){
	Queue* newQueue = createQueue();
	Element* q_copy = q->front;
	while(q_copy){
		enQueue(newQueue,q_copy->Teams->firstTeam,q_copy->Teams->secondTeam);
		q_copy = q_copy->next;
	}
	return newQueue;
}



