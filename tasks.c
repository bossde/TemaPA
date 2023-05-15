#include "header.h"

void Task1(char **argv, Team **TeamList){
    FILE *date,*output;
    
    int numberOfTeams;
    date = fopen(argv[2],"rt");
    output = fopen(argv[3],"wt");

    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);

        for(int i = 0; i < numberOfTeams; i++){
            fgetc(date);

            Team* Element = (Team*) malloc(sizeof(Team));
            Element->name = (char*) malloc(NAMES_LENGHT);
            Element->Players = (PlayerArray*) malloc(sizeof(PlayerArray));
            Element->nextTeam = NULL;
            fscanf(date,"%d", &Element->numberOfPlayers);
            fgetc(date);
            fscanf(date, "%[^\r]", Element->name);
            if(Element->name[strlen(Element->name) - 1] == ' '){
                Element->name[strlen(Element->name) - 1] = '\0';
            }

            PlayerArray* Auxiliar = Element->Players;
            for(int j = 0; j < Element->numberOfPlayers; j++){
                Auxiliar->player.firstName = (char*) malloc(NAMES_LENGHT);
                Auxiliar->player.secondName = (char*) malloc(NAMES_LENGHT);
                fscanf(date,"%s",Auxiliar->player.firstName);
                fscanf(date,"%s",Auxiliar->player.secondName);
                fscanf(date,"%d",&Auxiliar->player.points); 

                if (j < Element->numberOfPlayers - 1){
                    Auxiliar->next = (PlayerArray*) malloc(sizeof(PlayerArray));
                    Auxiliar = Auxiliar->next;
                } else {
                    Auxiliar->next = NULL;
                }
            }

            if (*TeamList == NULL){
                *TeamList = Element;
            } else {
                Team* Current = *TeamList;
                Element->nextTeam = Current;
                *TeamList = Element;
            }
        }
        PrintList(*TeamList, output);
    }
    fclose(output);
    fclose(date);
}

void Task2(Team** TeamList, char* argv[]){
    FILE* output, *input;
    int numberOfTeams,newNumberOfTeams, index;
    input = fopen(argv[2],"rt");
    if(input){
        fscanf(input,"%d",&numberOfTeams);
    }
    fclose(input);
    newNumberOfTeams = PowOf2(numberOfTeams);
    float *median, lowest_median;
    median = (float*) malloc(numberOfTeams * sizeof(float));
    Team *Auxiliar = NULL, *TeamToRemove = NULL;
    output = fopen(argv[3],"wt");
    if(output){
        while(numberOfTeams > newNumberOfTeams){
            Auxiliar = *TeamList;
            index = 0;
            lowest_median = FLT_MAX;
            while(Auxiliar){
                median[index] = MedianCalculator(Auxiliar);
                if(median[index] < lowest_median){
                    lowest_median = median[index];
                }
                index++;
                Auxiliar = Auxiliar->nextTeam;
            }

            TeamToRemove = *TeamList;

            for(int i = 0; i < numberOfTeams && TeamToRemove != NULL; i++){
                    if(median[i] == lowest_median){
                        RemoveTeam(TeamList,TeamToRemove);
                        break;
                    }
                    TeamToRemove = TeamToRemove->nextTeam;
            }
            
            numberOfTeams--;
            median = realloc(median,numberOfTeams * sizeof(float));
            for(int i = 0; i < numberOfTeams; i++){
                median[i] = 0;
            }
        }
    }
    Team* OutputTeams = *TeamList;
    while(OutputTeams){
        fprintf(output,"%s\n",OutputTeams->name);
        OutputTeams = OutputTeams->nextTeam;  
    }
    free(median);
    fclose(output);
}

void Task3(Team* TeamList, char** argv, Queue** WinnersTeams){
    FILE *output, *input;
    float TeamPoints[10];
    int PlayerPoints[10][100];
    int TeamContor = 0, PlayerContor = 0, number_of_players_in_team = 0;
    int number_of_teams, new_number_of_teams, number_of_round = 0;
    input = fopen(argv[2],"rt");
    fscanf(input,"%d", &number_of_teams);
    fclose(input);
    new_number_of_teams = PowOf2(number_of_teams);
    Queue* TeamsQueue = NULL;
    StackNode *Winners = NULL,*Losers = NULL;
    Element* q_copy = NULL;
    PlayerArray* PlayersInTeam;
    output = fopen(argv[3], "wt");
    *WinnersTeams = createQueue();
    *WinnersTeams = CreateQueue(*WinnersTeams,TeamList);
    CalculatePoints(*WinnersTeams);
    TeamsQueue = createQueue();
    TeamsQueue = CreateQueue(TeamsQueue,TeamList);
    CalculatePoints(TeamsQueue);
    PrintQueue(*WinnersTeams,output);
    while(new_number_of_teams != SEMI_FINAL){
        number_of_round++;
        fprintf(output,"--- ROUND NO:%d\n",number_of_round);
        PrintMatches(TeamsQueue,output);
        fprintf(output,"WINNERS OF ROUND NO:%d\n",number_of_round);
        CreateStacks(TeamsQueue,&Winners,&Losers);
        if(new_number_of_teams >= 16) recreateQueueFromWinnersStack(WinnersTeams,Winners);
        if(new_number_of_teams == 16){
            q_copy = (*WinnersTeams)->front;
            while(q_copy){
                TeamPoints[TeamContor] = q_copy->Teams->firstTeam->team_points;
                TeamContor++;
                PlayersInTeam = q_copy->Teams->firstTeam->Players;
                while(PlayersInTeam){
                    PlayerPoints[PlayerContor][number_of_players_in_team] = PlayersInTeam->player.points;
                    number_of_players_in_team++;
                    PlayersInTeam = PlayersInTeam->next;
                }
                PlayerContor++;
                number_of_players_in_team = 0;
                TeamPoints[TeamContor] = q_copy->Teams->secondTeam->team_points;
                TeamContor++;
                PlayersInTeam = q_copy->Teams->secondTeam->Players;
                while(PlayersInTeam){
                    PlayerPoints[PlayerContor][number_of_players_in_team] = PlayersInTeam->player.points;
                    number_of_players_in_team++;
                    PlayersInTeam = PlayersInTeam->next;
                }
                PlayerContor++;
                number_of_players_in_team = 0;
                q_copy = q_copy->next;
            }
        }
        recreateQueueFromWinnersStack(&TeamsQueue,Winners);
        PrintStack(&Winners,output);
        deleteStack(&Losers);
        deleteStack(&Winners);
        new_number_of_teams = new_number_of_teams / 2;
    }
    number_of_round++;
    TeamContor = 0;
    PlayerContor = 0;
    number_of_players_in_team = 0;
    fprintf(output,"--- ROUND NO:%d\n",number_of_round);
    PrintMatches(TeamsQueue,output);
    fprintf(output,"WINNERS OF ROUND NO:%d\n",number_of_round);
    CreateStacks(TeamsQueue,&Winners,&Losers);
    PrintStack(&Winners,output);
    deleteStack(&Losers);
    deleteStack(&Winners);
    free(TeamsQueue);
    q_copy = (*WinnersTeams)->front;
    while(q_copy){
        q_copy->Teams->firstTeam->team_points = TeamPoints[TeamContor];
        TeamContor++;
        PlayersInTeam = q_copy->Teams->firstTeam->Players;
        while(PlayersInTeam){
            PlayersInTeam->player.points = PlayerPoints[PlayerContor][number_of_players_in_team];
            number_of_players_in_team++;
            PlayersInTeam = PlayersInTeam->next;
        }
        PlayerContor++;
        number_of_players_in_team = 0;
        q_copy->Teams->secondTeam->team_points = TeamPoints[TeamContor];
        TeamContor++;
        PlayersInTeam = q_copy->Teams->secondTeam->Players;
        while(PlayersInTeam){
            PlayersInTeam->player.points = PlayerPoints[PlayerContor][number_of_players_in_team];
            number_of_players_in_team++;
            PlayersInTeam = PlayersInTeam->next;
        }
        PlayerContor++;
        number_of_players_in_team = 0;
        q_copy = q_copy->next;
    }
    free(PlayersInTeam);
    fclose(output);
}

void Task4(Queue* WinnersTeam, Team** TeamWinners, TreeNode** root, char** argv){
    FILE* output;
    output = fopen(argv[3],"at");
    QueueToList(WinnersTeam,TeamWinners);
    Team* AuxiliarList = *TeamWinners;
    while(AuxiliarList){
        *root = insert(*root, AuxiliarList);
        AuxiliarList = AuxiliarList->nextTeam;
    }
    fprintf(output,"\n");
    fprintf(output,"TOP 8 TEAMS:\n");
    PrintBST(*root,output);
    fclose(output);

}

void Task5(TreeNode* root, char** argv){
    FILE* output;
    output = fopen(argv[3],"at");
    if(output){

    }
}
