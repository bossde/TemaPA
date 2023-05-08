#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_TASKS 5

struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

struct PlayerArray{
    struct Player;
    struct PlayerArray *next;
};

typedef struct PlayerArray PlayerArray;

struct Team{
    char* name;
    int number_of_players;
    PlayerArray* Players;
    struct Team *nextTeam;
};

typedef struct Team Team;