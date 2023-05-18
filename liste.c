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

Team* reverseLinkedList(Team* head) {
    Team* prev = NULL;
    Team* current = head;
    Team* next = NULL;

    while (current != NULL) {
        next = current->nextTeam;
        current->nextTeam = prev;

    
        prev = current;
        current = next;
    }

    head = prev;
    
    return head;
}

void UpdateTeamPointsAndPlayerPoints(Queue** WinnersTeams, float* TeamPoints, int** PlayerPoints, int* TeamContor, int* PlayerContor, int* number_of_players_in_team, Element* q_copy) {
    while (q_copy) {
        q_copy->Teams->firstTeam->team_points = TeamPoints[*TeamContor];
        (*TeamContor)++;
        PlayerArray* PlayersInTeam = q_copy->Teams->firstTeam->Players;
        while (PlayersInTeam) {
            PlayersInTeam->player.points = PlayerPoints[*PlayerContor][*number_of_players_in_team];
            (*number_of_players_in_team)++;
            PlayersInTeam = PlayersInTeam->next;
        }
        (*PlayerContor)++;
        *number_of_players_in_team = 0;
        q_copy->Teams->secondTeam->team_points = TeamPoints[*TeamContor];
        (*TeamContor)++;
        PlayersInTeam = q_copy->Teams->secondTeam->Players;
        while (PlayersInTeam) {
            PlayersInTeam->player.points = PlayerPoints[*PlayerContor][*number_of_players_in_team];
            (*number_of_players_in_team)++;
            PlayersInTeam = PlayersInTeam->next;
        }
        (*PlayerContor)++;
        *number_of_players_in_team = 0;
        q_copy = q_copy->next;
    }
}

void UpdateTeamPointsAndPlayerPointsInRound8(Queue** WinnersTeams, float* TeamPoints, int** PlayerPoints) {
    int TeamContor = 0;
    int PlayerContor = 0;
    int number_of_players_in_team = 0;

    Element* q_copy = (*WinnersTeams)->front;
    while (q_copy) {
        TeamPoints[TeamContor] = q_copy->Teams->firstTeam->team_points;
        TeamContor++;
        PlayerArray* PlayersInTeam = q_copy->Teams->firstTeam->Players;
        while (PlayersInTeam) {
            PlayerPoints[PlayerContor][number_of_players_in_team] = PlayersInTeam->player.points;
            number_of_players_in_team++;
            PlayersInTeam = PlayersInTeam->next;
        }
        PlayerContor++;
        number_of_players_in_team = 0;

        TeamPoints[TeamContor] = q_copy->Teams->secondTeam->team_points;
        TeamContor++;
        PlayersInTeam = q_copy->Teams->secondTeam->Players;
        while (PlayersInTeam) {
            PlayerPoints[PlayerContor][number_of_players_in_team] = PlayersInTeam->player.points;
            number_of_players_in_team++;
            PlayersInTeam = PlayersInTeam->next;
        }
        PlayerContor++;
        number_of_players_in_team = 0;

        q_copy = q_copy->next;
    }

    UpdateTeamPointsAndPlayerPoints(WinnersTeams, TeamPoints, PlayerPoints, &TeamContor, &PlayerContor, &number_of_players_in_team, q_copy);
}

void UpdateTeamData(Element* winnersTeamsFront, float* teamPoints, int* teamContor, int** playerPoints, int* playerContor, int* numberOfPlayersInTeam) {
    Element* q_copy = winnersTeamsFront;
    while (q_copy) {
        q_copy->Teams->firstTeam->team_points = teamPoints[(*teamContor)];
        (*teamContor)++;
        PlayerArray* playersInTeam = q_copy->Teams->firstTeam->Players;
        while (playersInTeam) {
            playersInTeam->player.points = playerPoints[(*playerContor)][(*numberOfPlayersInTeam)];
            (*numberOfPlayersInTeam)++;
            playersInTeam = playersInTeam->next;
        }
        (*playerContor)++;
        (*numberOfPlayersInTeam) = 0;
        q_copy->Teams->secondTeam->team_points = teamPoints[(*teamContor)];
        (*teamContor)++;
        playersInTeam = q_copy->Teams->secondTeam->Players;
        while (playersInTeam) {
            playersInTeam->player.points = playerPoints[(*playerContor)][(*numberOfPlayersInTeam)];
            (*numberOfPlayersInTeam)++;
            playersInTeam = playersInTeam->next;
        }
        (*playerContor)++;
        (*numberOfPlayersInTeam) = 0;
        q_copy = q_copy->next;
    }
}

void FreeList(Team** TeamList) {
    Team* currentTeam = *TeamList;
    while (currentTeam) {
        free(currentTeam->name);
        
        PlayerArray* currentPlayer = currentTeam->Players;
        while (currentPlayer) {
            free(currentPlayer->player.firstName);
            free(currentPlayer->player.secondName);
            PlayerArray* nextPlayer = currentPlayer->next;
            free(currentPlayer);
            currentPlayer = nextPlayer;
        }
        
        Team* nextTeam = currentTeam->nextTeam;
        free(currentTeam);
        currentTeam = nextTeam;
    }
    
    *TeamList = NULL;
}



