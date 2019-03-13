// Jerico Factor
// PA 4 
// ID: 1674120 

// DigraphProperties.c

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Digraph.h"

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <inputfile> <outputfile>\n",argv[0]); 
		exit(1);
	}

	FILE* fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "w");

   if( fin==NULL )
   {
      printf("Unable to open file %s for reading\n", argv[1]);
      if(fout != NULL)
        fclose(fout); 
      exit(1);
   }
   if( fout==NULL )
   {
      printf("Unable to open file %s for writing\n", argv[2]);
      if(fin != NULL)
        fclose(fin);
      exit(1);
   }
	char *line = NULL; 
   	size_t len = 0;
  	size_t nread; 
  	char* token;

  	int vertex1; 
  	int vertex2; 

  	Digraph G = NULL;  

  	if((nread = getline(&line, &len, fin)) != -1)
  	{
  		token = strtok(line, " ,"); 
  		if (atoi(token) == 0)
  		{
  			fprintf(fout, "ERROR\n"); 
            fclose(fin); 
            fclose(fout); 
            free(line); 
  			exit(1);
  		}
        // printf("hello1\n"); 
  		G = newDigraph(atoi(token)); 
  		token = strtok(NULL, ", \r\n"); 
  		while(token != NULL)
  		{
  			vertex1 = atoi(token);
  			token = strtok(NULL, " "); 
  			vertex2 = atoi(token); 
			if (vertex1 > getOrder(G) || vertex1 < 1 || vertex2 > getOrder(G) || vertex2 < 1)
			{
				fprintf(fout, "ERROR\n"); 
				freeDigraph(&G); 
				free(line);
				fclose(fout);
				fclose(fin); 
                // printf("hello6\n");  
				exit(1); 
			}
            // printf("hello3\n"); 
  			addEdge(G, vertex1, vertex2); 
  			token = strtok(NULL, ", \r\n"); 
  		}
        // printf("hello6\n"); 
  	}
    if(G == NULL)
    {
        printf("graph not initialized"); 
    }
    // printf("\n"); 

  	// printDigraph(fout, G); printf("\n"); 
    // printf("hello9\n");
 	while ((nread = getline(&line, &len, fin)) != -1)
   	{
   		fprintf(fout, "%s", line); 
   		if(line[strlen(line)-1] != '\n' && line[strlen(line)-1] != '\r')
   			fprintf(fout, "\n" ); 
   		token = strtok(line, " \r\n");
   		while(token != NULL)
   		{
            if (strcmp(token, "PrintDigraph") == 0)
            {
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                printDigraph(fout, G); fprintf(fout, "\n"); 
                break; 
            }

            else if (strcmp(token, "GetOrder") == 0)
            {
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout, "%d\n", getOrder(G)); 
                break; 
            }

            else if(strcmp(token, "GetSize") == 0)
            {
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout, "%d\n", getSize(G));
                break; 
            }

            else if(strcmp(token, "GetOutDegree") == 0)
            {
                token = strtok(NULL, " \n\r");
                if (token == NULL)
                {
                    fprintf(fout, "ERROR\n"); 
                    break; 
                }
                int value = atoi(token); 
                if (getOutDegree(G, value) == -1)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout, "%d\n", getOutDegree(G, value)); 
                break; 
            }

            else if(strcmp(token, "AddEdge") == 0)
            { 
                
                int arr[2] = {-1,-1};
                for(int i = 0; i < 2; i++)
                {
                    token = strtok(NULL, " \n"); 
                    if(token == NULL)
                    {
                        fprintf(fout, "ERROR\n"); 
                        break; 
                    }
                    arr[i] = atoi(token); 
                }
                if (arr[0] < 1 || arr[0] > getOrder(G) || arr[1] < 1 || arr[1] > getOrder(G))
                {
                    fprintf(fout, "ERROR\n"); 
                    break;
                }
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout,"%d\n",addEdge(G, arr[0], arr[1])); 
                break; 
            }

            else if(strcmp(token, "DeleteEdge") == 0)
            { 
                
                int arr[2] = {-1,-1};
                for(int i = 0; i < 2; i++)
                {
                    token = strtok(NULL, " \n"); 
                    if(token == NULL)
                    {
                        fprintf(fout, "ERROR\n"); 
                        break; 
                    }
                    arr[i] = atoi(token); 
                }
                if (arr[0] == -1)
                    break;
                if (arr[1] == -1)
                    break;
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout,"%d\n",deleteEdge(G, arr[0], arr[1])); 
                break; 
            }

            else if (strcmp(token, "GetCountSCC") == 0)
            {
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout, "%d\n", getCountSCC(G)); 
                break; 
            }

            else if(strcmp(token, "GetNumSCCVertices") == 0)
            {
                token = strtok(NULL, " \n\r");
                if (token == NULL)
                {
                    fprintf(fout, "ERROR\n"); 
                    break; 
                }
                int value = atoi(token); 
                if (getOutDegree(G, value) == -1)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                fprintf(fout, "%d\n", getNumSCCVertices(G, value)); 
                break; 
            }

            else if(strcmp(token, "InSameSCC") == 0)
            { 
                
                int arr[2] = {-1,-1};
                for(int i = 0; i < 2; i++)
                {
                    token = strtok(NULL, " \n"); 
                    if(token == NULL)
                    {
                        fprintf(fout, "ERROR\n"); 
                        break; 
                    }
                    arr[i] = atoi(token); 
                }
                if (arr[0] == -1)
                    break;
                if (arr[1] == -1)
                    break;
                token = strtok(NULL," \r\n");
                if(token != NULL)
                {
                    fprintf(fout, "ERROR\n");
                    break;  
                }
                if(inSameSCC(G, arr[0], arr[1]))
                    fprintf(fout, "YES\n");
                else
                    fprintf(fout, "NO\n");
                break; 
            }

   			fprintf(fout, "ERROR\n"); 
   			break; 
   		}
   	}

    free(line); 
  	freeDigraph(&G); 
	fclose(fin); 
	fclose(fout); 
}