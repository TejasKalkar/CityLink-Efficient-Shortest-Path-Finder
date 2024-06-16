#include<ctype.h>
#include<limits.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

//Function declarations
int findMinimumDistanceCity(int distance[],bool processedCities[],int numCities);
void computeDijkstra(int **cityMap, int source, int numCities, int destination);
void clearScreen();
int **generateCityMap(int numCities,int links);


int main()
{
    int numCities,links;

    //Start
    printf("Welcome to CityLink!\n");
    printf("This program efficiently helps you to find the shortest travel routes between cities.\n ");
    printf("Let's get started!\n");

    //User input for the number of cities and links
    printf("Enter the number of cities: ");
    scanf("%d",&numCities);
    printf("Enter the total number of links: ");
    scanf("%d",&links);

    //Generate adjacency matrix for the city network based on user input
    int** cityMap = generateCityMap(numCities, links);
    int src,dest;
    printf("\nNote: The cities are named from 0 to %d. \n",numCities-1);
    printf("Enter the source city: ");
    scanf("%d",&src);
    printf("Enter the destination city: ");
    scanf("%d",&dest);

    //Compute and display the shortest path between the source and destination cities
    computeDijkstra(cityMap, src, numCities, dest);

    //Main menu loop
    while (true){
        int choice;
        printf("\nEnter your choice(from 1 to 4):\n");
        printf("1. Find shortest path for other source and destination cities for the same network of travel route\n");
        printf("2. Update the network of travel routes\n");
        printf("3. Clear screen\n");
        printf("4. Exit\n");
        scanf("%d",&choice);

        switch (choice){
            case 1:
                printf("\nEnter the new source city: ");
                scanf("%d",&src);
                printf("Enter the new destination city: ");
                scanf("%d",&dest);
                computeDijkstra(cityMap, src, numCities, dest);
                break;
            case 2:
                //Free memory for the existing city map
                for (int i = 0; i < numCities; i++){
                    free(cityMap[i]);
                }
                free(cityMap);

                //Update city network based on user input
                printf("\nEnter the number of cities: ");
                scanf("%d", &numCities);
                printf("Enter the total number of links: ");
                scanf("%d", &links);

                cityMap = generateCityMap(numCities, links);

                printf("Enter the source city: ");
                scanf("%d", &src);
                printf("Enter the destination city: ");
                scanf("%d", &dest);
                computeDijkstra(cityMap, src, numCities, dest);
                break;
            case 3:
                clearScreen();
                break;
            case 4:
                printf("\nExting CityLink. Hope you enjoyed!\n ");
                goto exit_loop;
            default:
                printf("\nInvalid choice\n");
        }       
    }

    //Free allocated memory before exiting
    exit_loop:
    for (int i = 0; i < numCities; i++){
        free(cityMap[i]);
    }
    free(cityMap);

    return 0;   
}

//Function to find the city with minimum distance value
int findMinimumDistanceCity(int distance[], bool processedCities[], int numCities)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < numCities; v++)
    if (processedCities[v] == false && distance[v] <= min)
        min = distance[v], min_index = v;

    return  min_index;
}

//Function to compute shortest path using Dijkstra's algorithm
void computeDijkstra(int** cityMap, int source, int numCities, int destination)
{
    int distance[numCities];
    bool processedCities[numCities];

    //Initialization
    for (int i = 0; i < numCities; i++)
        distance[i] = INT_MAX, processedCities[i] = false;

    distance[source] = 0;

    for (int count = 0; count < numCities - 1; count++){
        int u = findMinimumDistanceCity(distance, processedCities, numCities);
        processedCities[u] = true;
        for (int v = 0; v < numCities; v++)
            if( !processedCities[v] && cityMap[u][v] &&
                distance[u] != INT_MAX &&
                distance[u] + cityMap[u][v] < distance[v] )
                distance[v] = distance[u] + cityMap[u][v];
    }

    //Display shortest distance from source to destination city
    printf("\nDistance from city %d to city %d: %d\n", source, destination, distance[destination]);       
}

//Function to clear the screen
void clearScreen() {
    system("clear");
}

int** generateCityMap(int numCities, int links){
    int** cityMap = (int**)malloc(numCities * sizeof(int*));
    for (int i = 0; i < numCities; i++){
        cityMap[i] = (int*)malloc(numCities * sizeof(int));
        for (int j = 0; j < numCities; j++) {
            cityMap[i][j] = 0; //Initialize all elements to 0
        }
    }

    printf("\nEnter the distance between cities:\n");
    for (int i = 0; i < links; i++){
        int city1, city2, distance;
        printf("Enter cities and distance for link %d (city1 city2 distance): ",i + 1);
        scanf("%d %d %d", &city1, &city2, &distance);
        if (city1 >= numCities || city2 >= numCities){
            printf("Invalid city entered. Please enter cities in the range [0,%d].\n", numCities - 1);
            i--;//Decrement the counter to re-enter the current link
            continue;
        } 
        cityMap[city1][city2] = cityMap[city2][city1] = distance; //Undirected graph
    }

        return cityMap;
        
    
    }




