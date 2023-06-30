#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 7
#define INF 999999

typedef struct {
    int matrix[MAX_NODES][MAX_NODES];
    int numNodes;
} Graph;

void initGraph(Graph* graph, int numNodes) {
    graph->numNodes = numNodes;

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph->matrix[i][j] = INF;
        }
    }
}

void addEdge(Graph* graph, int source, int dest, int weight) {
    graph->matrix[source][dest] = weight;
    graph->matrix[dest][source] = weight;
}

int findMinDistance(int dist[], bool visited[], int numNodes) {
    int minDist = INF;
    int minIndex = -1;

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i] && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void printPath(int parent[], int node) {
    if (parent[node] == -1) {
        printf("%c ", node + 'A');
        return;
    }

    printPath(parent, parent[node]);
    printf("%c ", node + 'A');
}

void dijkstra(Graph* graph, int source, int dest) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < graph->numNodes; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < graph->numNodes - 1; count++) {
        int u = findMinDistance(dist, visited, graph->numNodes);

        visited[u] = true;

        for (int v = 0; v < graph->numNodes; v++) {
            if (!visited[v] && graph->matrix[u][v] != INF &&
                dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->matrix[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Caminho mínimo: ");
    printPath(parent, dest);
    printf("\nDistância total: %d\n", dist[dest]);
}

int main() {
    Graph graph;

    initGraph(&graph, MAX_NODES);

    int matrix[MAX_NODES][MAX_NODES] = {
        {0, 5, 0, 0, 0, 3, 0},
        {5, 0, 20, 0, 2, 0, 3},
        {0, 20, 0, 3, 0, 10, 0},
        {0, 0, 3, 4, 0, 0, 0},
        {0, 2, 0, 4, 0, 1, 1},
        {3, 0, 10, 0, 1, 0, 0},
        {0, 3, 0, 0, 1, 0, 0}
    };

    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            if (matrix[i][j] != 0) {
                addEdge(&graph, i, j, matrix[i][j]);
            }
        }
    }

    int source = 0; // 0 = A   G = 6
    int dest = 2; 

    dijkstra(&graph, source, dest);

    return 0;
}

