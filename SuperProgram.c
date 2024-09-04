#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void addEdge(int **graph, int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void printGraph(int **graph, int V) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void DFS(int **graph, int V, int *visited, int v) {
    visited[v] = 1;
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            DFS(graph, V, visited, i);
        }
    }
}

bool isConnected(int **graph, int V) {
    int *visited = (int *)calloc(V, sizeof(int));
    int startVertex = -1;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 1) {
                startVertex = i;
                break;
            }
        }
        if (startVertex != -1) break;
    }

    if (startVertex == -1) {
        free(visited);
        return false;
    }

    DFS(graph, V, visited, startVertex);

    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            free(visited);
            return false;
        }
    }

    free(visited);
    return true;
}



bool isEulerian(int **graph, int V) {
    int oddDegree = 0;

    for (int i = 0; i < V; i++) {
        int degree = 0;
        for (int j = 0; j < V; j++) {
            if (graph[i][j]) degree++;
        }
        if (degree % 2 != 0) oddDegree++;
    }

    return (oddDegree == 0 || oddDegree == 2) && isConnected(graph, V);
}

bool isHamiltonianUtil(int **graph, int V, int path[], int pos) {
    if (pos == V) {
        return (graph[path[pos - 1]][path[0]] == 1);
    }

    for (int v = 1; v < V; v++) {
        bool alreadyInPath = false;
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                alreadyInPath = true;
                break;
            }
        }
        if (alreadyInPath || graph[path[pos - 1]][v] == 0) {
            continue;
        }

        path[pos] = v;
        if (isHamiltonianUtil(graph, V, path, pos + 1)) {
            return true;
        }
        path[pos] = -1;
    }
    return false;
}

bool isHamiltonian(int **graph, int V) {
    int *path = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        path[i] = -1;
    }
    path[0] = 0;
    bool result = isHamiltonianUtil(graph, V, path, 1);
    free(path);
    return result;
}

int main() {
    int V, numEdges, u, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)calloc(V, sizeof(int));
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Enter edge %d (format u v): ", i + 1);
        scanf("%d %d", &u, &v);

        if (u >= V || v >= V || u < 0 || v < 0) {
            printf("Error: vertices must be between 0 and %d.\n", V - 1);
            i--;
        } else {
            addEdge(graph, u, v);
        }
    }

    printGraph(graph, V);

    if (isEulerian(graph, V)) {
        printf("The graph is Eulerian\n");
    } else {
        printf("The graph is not Eulerian\n");
    }

    if (isHamiltonian(graph, V)) {
        printf("The graph is Hamiltonian\n");
    } else {
        printf("The graph is not Hamiltonian\n");
    }

    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}