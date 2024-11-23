#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 5

// Function to calculate factorial
int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

// Function to find the minimum cost using the TSP algorithm
void tsp(int graph[MAX_N][MAX_N], int n, int path[MAX_N], int visited[MAX_N], int cost, int level, int* minCost, int* minPath) {
    if (level == n) {
        // Complete the cycle
        cost += graph[path[level - 1]][path[0]];

        // Update the minimum cost and path
        if (cost < *minCost) {
            *minCost = cost;
            for (int i = 0; i < n; i++)
                minPath[i] = path[i];
        }
        return;
    }

    // Try different next nodes
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            path[level] = i;

            // Recur to the next level
            tsp(graph, n, path, visited, cost + graph[path[level - 1]][i], level + 1, minCost, minPath);

            // Backtrack
            visited[i] = 0;
        }
    }
}

int main() {
    // Variables for TSP
    int path[MAX_N];
    int visited[MAX_N] = {0};
    int minCost = INT_MAX;
    int minPath[MAX_N];

    // Input: Number of locations
    int n;
    printf("\nEnter the number of locations (maximum %d): ", MAX_N);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_N) {
        printf("Invalid number of locations. Exiting...\n");
        return 1;
    }

    // Input: Graph distances
    int graph[MAX_N][MAX_N];
    printf("\nEnter the distance matrix for the graph:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("\nDistance from location %d to location %d: ", i, j);
            scanf("%d", &graph[i][j]);
        }
    }

    // Starting node (can be any node)
    int startNode;
    printf("\nEnter the starting location (0 to %d): ", n - 1);
    scanf("%d", &startNode);

    if (startNode < 0 || startNode >= n) {
        printf("Invalid starting location. Exiting...\n");
        return 1;
    }

    // Initialize path
    path[0] = startNode;
    visited[startNode] = 1;

    // Solve the TSP problem
    tsp(graph, n, path, visited, 0, 1, &minCost, minPath);

    // Print the result
    printf("Minimum Cost: %d\n", minCost);
    printf("Optimal Path: ");
    for (int i = 0; i < n; i++)
        printf("%d -> ", minPath[i]);
    printf("%d\n", minPath[0]);

    return 0;
}
