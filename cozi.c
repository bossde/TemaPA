#include "header.h"

Queue* createQueue(){
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	if (q == NULL) return NULL;	
	q->front = q->rear=NULL;
	return q;	
}

 void enQueue(Queue*q, Team* v){
	Element* newNode = (Element*)malloc(sizeof(Element));
	newNode->TeamQueue = v;
	newNode->next = NULL;
	if (q->rear == NULL) q->rear = newNode; 
	else{
		(q->rear)->next = newNode;
		(q->rear) = newNode;
	}
	if (q->front == NULL) q->front = q->rear; 
}
 
Team* deQueue(Queue*q) {  
	Element* aux; Team* d;
	if (isEmpty(q)) return NULL;
	aux = q->front; 
	d = aux->TeamQueue;
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

void PrintQueue(Queue* q, FILE* output){
	Element* q_copy = q->front;
	while(q_copy != NULL){
		fprintf(output, "%s\n", q_copy->TeamQueue->name);
		q_copy = q_copy->next;
	}
	fprintf(output,"\n");
}

void PrintMatches(Queue* q, FILE* output){
	Element* q_copy = q->front;
        while(q_copy && q_copy->next){
            fprintf(output,"%s - %s\n",q_copy->TeamQueue->name,q_copy->next->TeamQueue->name);
            q_copy = q_copy->next->next;
        }
	fprintf(output,"\n");
}

void CalculatePoints(Queue *q){
	Element* q_copy = q->front;
	while(q_copy){
		q_copy->TeamQueue->team_points = MedianCalculator(q_copy->TeamQueue);
		q_copy = q_copy->next;
	}
}
