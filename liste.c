#include "header.h"

void PrintList(Team* TeamList, FILE* output){
	while(TeamList){
		fprintf(output,"%s\n",TeamList->name);
		TeamList = TeamList->nextTeam;
	}
}

float MedianCalculator(Team* TeamMedian){
	float median = 0;
	int numberOfSums = 0;
	PlayerArray* Current = TeamMedian->Players;
	while(Current != NULL){
		median += Current->player.points;
		numberOfSums++;
		Current = Current->next;
	}
	median = median / numberOfSums;
	return median;
}

int PowOf2(int numberOfTeams){
	int value = 1;
	while(value <= numberOfTeams){
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

    if (current == NULL) {
        return;
    }
	
    if(TeamToDelete == NULL){
        return;
    }
    
    if (TeamToDelete->nextTeam != NULL) {
        current->nextTeam = TeamToDelete->nextTeam;
    } else {
        current->nextTeam = NULL;
    }

    free(TeamToDelete);
}


Team* copyTeam(Team* source, Team* destination){
    int nameLength = strlen(source->name) + 1;
    destination->name = (char*) malloc(nameLength);
    strcpy(destination->name, source->name);

    destination->numberOfPlayers = source->numberOfPlayers;

    PlayerArray* sourcePlayer = source->Players;
    PlayerArray* destinationPlayer = (PlayerArray*) malloc(sizeof(PlayerArray));
    destination->Players = destinationPlayer;

    while(sourcePlayer != NULL){
        destinationPlayer->player = sourcePlayer->player;
        if(sourcePlayer->next != NULL){
            destinationPlayer->next = (PlayerArray*) malloc(sizeof(PlayerArray));
            destinationPlayer = destinationPlayer->next;
        }
        else{
            destinationPlayer->next = NULL;
        }
        sourcePlayer = sourcePlayer->next;
    }

    destination->nextTeam = source->nextTeam;
	return destination;
}
