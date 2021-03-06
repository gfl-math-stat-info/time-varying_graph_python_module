#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct edge
{
    int from;
    int to;
};

char* concat(char* stringStart, char* stringEnd){
	char *result = malloc(strlen(stringStart) + strlen(stringEnd) + 1);
	strcpy(result, stringStart);
    strcat(result, stringEnd);
}

/* main() returns int, not void. */
int main(int argc, char *argv[] ) {
	
	if(argc != 3) {
		printf("Expected exactly 2 arguments. Terminating. \n" );
		return 1;
	}
	char showgStringCall[] = "./G6_Deserializer.exe -e ";
	char *result = concat(showgStringCall, argv[1]);

	FILE *fp;
	char* line = NULL;
	size_t size = 0;
	
	fp = popen(result, "r");
	if (fp == NULL) {
		printf("Failed to run Showg\n" );
		exit(1);
	}
	
	int edgesNumber = -1;
	struct edge* edges;
	int edgeCount = 0;
	/* Read the output a line at a time - output it. */
	while (getline(&line, &size, fp) != -1) {
		if (strstr(line, "Graph") == NULL) {
			if(line[0] == '\n') {
				//New graph
			}
			else if(edgesNumber == -1){ //Begining of the edge list
				int j = 0;
				while(isdigit(line[j++]));
				char edgCnt[2];
				edgCnt[0] = line[j];
				edgCnt[1] = '\0';
				while(isdigit(line[++j])){
					strncat(edgCnt, &line[j], 1);
				}
				edgesNumber = atoi(edgCnt);
				edges = (struct edge*)malloc(sizeof(struct edge)*edgesNumber);
			}
			else {
				for(int i = 0; i < strlen(line); i++) {
					if(isdigit(line[i])) {
						char from[2];
						from[0] = line[i];
						from[1] = '\0';
						while(isdigit(line[++i])) {
							strncat(from, &line[i], 1);
						}
						edges[edgeCount].from = atoi(from);
						char to[2];
						if(isdigit(line[++i])) {
							to[0] = line[i];
							to[1] = '\0';
							while(isdigit(line[++i])) {
								strncat(to, &line[i], 1);
							}
							edges[edgeCount].to = atoi(to);
						}
						else {
							printf("Showg format error\n" );
						}
						edgeCount++;
					}
				}
				break;
			}
		}  
		free(line);
		line = NULL;
	}
	fclose(fp);
	free(result);
	
	char binaryChains[edgesNumber][255];
	char fileLine[255];
	edgeCount = 0;
	
	fp = fopen(argv[2], "r");
	
	while (fgets(fileLine, sizeof(fileLine), fp) != NULL) {
	    if(edgeCount == edgesNumber) {
			printf("Too many binary chains. Terminating. \n" );
			return 1;
		}
		strcpy(binaryChains[edgeCount++], fileLine);
		
	}
	
	if(edgeCount != edgesNumber) {
		printf("Not enough binary chains. Terminating. \n" );
		return 1;
	}
	
	for(int i =0; i < edgesNumber; i++) {
		printf("(%d, %d) ??? %s \n", edges[i].from, edges[i].to, binaryChains[i]);
	}
	
	
	free(edges);
	return 0;
}

