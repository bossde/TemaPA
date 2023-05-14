#include "header.h"

void Task1(char **argv, Team **TeamList){
    FILE *date,*output;
    char c;
    int numberOfTeams;
    date = fopen(argv[2],"rt");
    output = fopen(argv[3],"wt");

    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);

        for(int i = 0; i < numberOfTeams; i++){
            c = fgetc(date);

            Team* Element = (Team*) malloc(sizeof(Team));
            Element->name = (char*) malloc(NAMES_LENGHT);
            Element->Players = (PlayerArray*) malloc(sizeof(PlayerArray));
            Element->nextTeam = NULL;
            fscanf(date,"%d", &Element->numberOfPlayers);
            c = fgetc(date);
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

void Task3(Team* TeamList, char** argv, StackNode** WinnerTeams){
    FILE *output, *input;
    int number_of_teams, new_number_of_teams, number_of_round = 0;
    input = fopen(argv[2],"rt");
    fscanf(input,"%d", &number_of_teams);
    fclose(input);
    new_number_of_teams = PowOf2(number_of_teams);
    Queue *q = NULL;
    StackNode *Winners = NULL;
    StackNode *Losers = NULL;
    output = fopen(argv[3], "wt");
    q = createQueue();
    q = CreateQueue(q,TeamList);
    CalculatePoints(q);
    PrintQueue(q,output);

    while(new_number_of_teams != SEMI_FINAL){
        number_of_round++;
        fprintf(output,"--- ROUND NO:%d\n",number_of_round);
        PrintMatches(q,output);
        fprintf(output,"WINNERS OF ROUND NO:%d\n",number_of_round);
        CreateStacks(q,&Winners,&Losers);
        recreateQueueFromWinnersStack(&q,Winners);
        PrintStack(&Winners,output);
        deleteStack(&Losers);
        deleteStack(&Winners);
        new_number_of_teams = new_number_of_teams / 2;
    }
    number_of_round++;
    fprintf(output,"--- ROUND NO:%d\n",number_of_round);
    PrintMatches(q,output);
    fprintf(output,"WINNERS OF ROUND NO:%d\n",number_of_round);
    CreateStacks(q,&Winners,&Losers);
    PrintStack(&Winners,output);
    deleteStack(&Losers);
    deleteStack(&Winners);
    free(q);
    fclose(output);
}

void Task4(){

}

void Task5(){
    
}
