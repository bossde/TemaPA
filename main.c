#include "header.h"

int main(int argc, char **argv){
    int* tasks;
    tasks = (int*) malloc(NUMBER_OF_TASKS * sizeof(int));
    FILE* file;
    FILE* output = fopen(argv[3],"wt");
    TreeNode* root = NULL,*avlroot = NULL;
    Queue* WinnerTeams = NULL;
    Team *TeamList = NULL,*NewTeamList = NULL;
    file = fopen(argv[1],"rt");
    if(file != NULL){
    for(int i = 0; i < NUMBER_OF_TASKS; i++){
        fscanf(file,"%d",&tasks[i]);
    }
    fclose(file);
    }
    if(tasks[0] == 1){
        Task1(argv,&TeamList);
    }

    if(tasks[1] == 1){
        Task2(&TeamList,argv);
    }

    if(tasks[2] == 1){
        Task3(TeamList,argv,&WinnerTeams);

    }

    if(tasks[3] == 1){
        Task4(WinnerTeams,&NewTeamList,&root,argv);
    }

    if(tasks[4] == 1){
        Task5(&avlroot, root, argv);
    }
    fclose(output);
    return 0;
}
    