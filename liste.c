#include "header.h"

void PrintList(Team* TeamList, char** argv){
	FILE* output = fopen(argv[3],"wt");
	while(TeamList){
		fprintf(output,"%s\n",TeamList->name);
		TeamList = TeamList->nextTeam;
	}
}