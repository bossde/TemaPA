#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define NUMBER_OF_TASKS 5
#define NAMES_LENGHT 80
#define WINNER_TEAMS 8

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
    float team_points;
    PlayerArray *Players;
    struct Team *nextTeam;
};

typedef struct Team Team;



struct Element{
    Team* TeamQueue;
    struct Element* next;
};

typedef struct Element Element;

struct Q{
    Element *front,*rear;
};

typedef struct Q Queue;


struct StackElement{
    Team* StackTeam;
    struct StackElement* next;
};

typedef struct StackElement StackNode;

void Task1(char** argv, Team** TeamList);
void Task2(Team** TeamList, char** argv);
void Task3(Team** TeamList, char** argv, StackNode** WinnerTeams);
void PrintList(Team* TeamList, FILE* output);
float MedianCalculator(Team* TeamMedian);
int PowOf2(int numberOfTeams);
void RemoveTeam(Team** TeamHead, Team* TeamToDelete);
Team* copyTeam(Team* source, Team* destination);
Queue* createQueue();
void enQueue(Queue*q, Team *v);
Team* deQueue(Queue*q);
int isEmpty(Queue*q);
void deleteQueue(Queue*q);
Team* top(StackNode *top);
void push(StackNode**top, Team* v);
Team* pop(StackNode**top);
int isEmptyStack(StackNode*top);
void deleteStack(StackNode**top);
void deleteStack(StackNode**top);
void PrintQueue(Queue* q, FILE* output);
void PrintMatches(Queue* q, FILE* output);
void CalculatePoints(Queue *q);
void PrintStack(StackNode*top, FILE* output);
void RecreateQueue(Queue* q, StackNode* Winners);