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
    FILE* output, *input;
    int numberOfTeams,newNumberOfTeams;
    input = fopen(argv[2],"rt");
    if(input){
        fscanf(input,"%d",&numberOfTeams);
    }
    fclose(input);
    newNumberOfTeams = PowOf2(numberOfTeams);
    float median, lowest_median = FLT_MAX;
    Team *Auxiliar = *TeamList, *LeastPoints = (Team*) malloc(sizeof(Team));
    LeastPoints->name = (char*) malloc(NAMES_LENGHT);
    output = fopen(argv[3],"wt");
    if(output){
        while(numberOfTeams > newNumberOfTeams){
            Auxiliar = *TeamList;
            while(Auxiliar){
                median = MedianCalculator(Auxiliar);
                if(median < lowest_median){
                    lowest_median = median;
                    LeastPoints = copyTeam(Auxiliar,LeastPoints);
                    fprintf(output,"%s\n",LeastPoints->name);
                }
                Auxiliar = Auxiliar->nextTeam;
            }
            Auxiliar = *TeamList;
            while(Auxiliar){
    if(strcmp(LeastPoints->name,Auxiliar->name) == 0){
        RemoveTeam(TeamList,Auxiliar);
        Auxiliar = *TeamList;  
        break;
    }
    Auxiliar = Auxiliar->nextTeam;
}

            numberOfTeams--;
        }
    }
    fclose(output);
}

void Task3(){

}

void Task4(){

}
