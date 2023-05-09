#include "header.h"

void PrintList(Team* TeamList, FILE* output){
	while(TeamList){
		fprintf(output,"%s\n",TeamList->name);
		TeamList = TeamList->nextTeam;
	}
}

float MedianCalculator(PlayerArray* Players){
    if (Players == NULL) {
        return 0.0;
    }

    int median = 0;
    int numberOfOperations = 0;

    while(Players){
        median += Players->player.points;
        numberOfOperations++;
        Players = Players->next;
    }

    return (float)(median/numberOfOperations);
}

int PowOf2(int numberOfTeams){
	int value = 1;
	while(value < numberOfTeams){
		value = 2 * value;
	}
	return value/2;
}

void RemoveTeam(Team** TeamHead, Team* TeamToDelete) {
    if (*TeamHead == TeamToDelete) {
        *TeamHead = TeamToDelete->nextTeam;
        free(TeamToDelete);
        return;
    }

    Team* current = *TeamHead;
    while (current != NULL && current->nextTeam != TeamToDelete) {
        current = current->nextTeam;
    }

    current->nextTeam = TeamToDelete->nextTeam;
    free(TeamToDelete);
}