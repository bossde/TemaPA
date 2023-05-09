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
    FILE *output,*input;
    float median, minimal_median = FLT_MAX;
    int numberOfPlayers, newNumberOfPlayers;
    input = fopen(argv[2],"rt");
    if(input){
        fscanf(input,"%d",&numberOfPlayers);
    }
    fclose(input);
    newNumberOfPlayers = PowOf2(numberOfPlayers);
    output = fopen(argv[3],"wt");
    fprintf(output,"%d %d",numberOfPlayers,newNumberOfPlayers);
    Team* LeastPoints = NULL, *Auxiliar = NULL;
    LeastPoints = (Team*) malloc(sizeof(Team));
    LeastPoints->name = (char*) malloc(NAMES_LENGHT);
    while(numberOfPlayers > newNumberOfPlayers){
    Auxiliar = *TeamList;
    while(Auxiliar != NULL){
        median = MedianCalculator(Auxiliar->Players);
        if(median < minimal_median){
            minimal_median = median;
            strcpy(LeastPoints->name, Auxiliar->name);
        }
        break;
        Auxiliar = Auxiliar->nextTeam;
    }

    Auxiliar = *TeamList;
        while(Auxiliar){
        if(Auxiliar->nextTeam = LeastPoints) {
            RemoveTeam(TeamList, Auxiliar->nextTeam);
            break;
        }
    }

    numberOfPlayers--;

    }
    fclose(output);
}

void Task3(){

}

void Task4(){

}
