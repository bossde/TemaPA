#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define NUMBER_OF_TASKS 5
#define NAMES_LENGHT 80

struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

struct PlayerArray{
    struct Player player;
    struct PlayerArray *next;
};

typedef struct PlayerArray PlayerArray;

struct Team{
    char *name;
    int numberOfPlayers;
    PlayerArray *Players;
    struct Team *nextTeam;
};

typedef struct Team Team;

void Task1(char** argv, Team** TeamList);
void Task2(Team** TeamList, char** argv);
void PrintList(Team* TeamList, FILE* output);
float MedianCalculator(PlayerArray* Players);
int PowOf2(int numberOfTeams);
void RemoveTeam(Team** TeamHead, Team* TeamToDelete);