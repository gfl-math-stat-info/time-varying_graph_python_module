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

struct dynamic_edge
{
	struct edge;
	char* appearanceTable[];
};

/* main() returns int, not void. */
int main( void ) {

  FILE *fp;
  char path[1035];
  
  fp = popen("./G6_Deserializer.exe -e graph.g6", "r");
   if (fp == NULL) {
    printf("Failed to run Showg\n" );
    exit(1);
  }
  
  int edgesNumber = -1;
  struct edge* edges;
  int edgeCount = 0;
  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path), fp) != NULL) {
	if (strstr(path, "Graph") == NULL) {
		if(path[0] == '\n') {
			
		}
		else if(edgesNumber == -1){
			int j = 0;
			while(isdigit(path[j++]));
			char edgCnt[2];
			edgCnt[0] = path[j];
			edgCnt[1] = '\0';
			while(isdigit(path[++j])){
				strncat(edgCnt, &path[j], 1);
			}
			edgesNumber = atoi(edgCnt);
			edges = (struct edge*)malloc(sizeof(struct edge)*edgesNumber);
		}
		else {
			for(int i = 0; i < strlen(path); i++) {
				if(isdigit(path[i])) {
					 char from[2];
					 from[0] = path[i];
					 from[1] = '\0';
					 while(isdigit(path[++i])) {
						 strncat(from, &path[i], 1);
					 }
					 edges[edgeCount].from = atoi(from);
					 char to[2];
					 if(isdigit(path[++i])) {
						 to[0] = path[i];
						 to[1] = '\0';
						 while(isdigit(path[++i])) {
							strncat(to, &path[i], 1);
						}
						edges[edgeCount].to = atoi(to);
					 }
					 else {
						 printf("Showg format error\n" );
					 }
					printf("(%d, %d)\n", edges[edgeCount].from, edges[edgeCount].to);
					edgeCount++;
				}
			}
			break;
		}
	}  
  }
  free(edges);
  return 0;
}