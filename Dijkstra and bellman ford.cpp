#include <stdio.h>
#include <stdbool.h>

void dijkstra(int graph[20][20], int n, int src) {
    int dist[n], visited[n];
    for (int i = 0; i < n; i++) {
        dist[i] = 1000000;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Dijkstra distances from source %d:\n", src);
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

void bellmanFord(int edges[20][3], int n, int e, int src) {
    int dist[n];
    for (int i = 0; i < n; i++) {
        dist[i] = 1000000;
    }
    dist[src] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < e; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int weight = edges[j][2];
            if (dist[u] != 1000000 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int j = 0; j < e; j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int weight = edges[j][2];
        if (dist[u] != 1000000 && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }

    printf("Bellman-Ford distances from source %d:\n", src);
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

int main() {
    int n, choice;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Choose algorithm:\n1. Dijkstra (Adjacency Matrix)\n2. Bellman-Ford (Edge List)\n");
    scanf("%d", &choice);

    if (choice == 1) {
        int graph[20][20];
        printf("Enter the adjacency matrix:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &graph[i][j]);
            }
        }
        int src;
        printf("Enter the source vertex: ");
        scanf("%d", &src);
        dijkstra(graph, n, src);
    } else if (choice == 2) {
        int e;
        printf("Enter the number of edges: ");
        scanf("%d", &e);
        int edges[20][3];
        printf("Enter the edges (u v weight):\n");
        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
        }
        int src;
        printf("Enter the source vertex: ");
        scanf("%d", &src);
        bellmanFord(edges, n, e, src);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
