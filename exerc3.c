#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct ListaAdj {
    No* cabeca;
} ListaAdj;

typedef struct Grafo {
    int numVertices;
    ListaAdj* lista;
    int* visitado;
} Grafo;

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->lista = (ListaAdj*)malloc(vertices * sizeof(ListaAdj));
    grafo->visitado = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        grafo->lista[i].cabeca = NULL;
        grafo->visitado[i] = 0;
    }

    return grafo;
}

No* criarNo(int v) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->prox = NULL;
    return novoNo;
}

void adicionarAresta(Grafo* grafo, int src, int dest) {
    No* novoNo = criarNo(dest);
    novoNo->prox = grafo->lista[src].cabeca;
    grafo->lista[src].cabeca = novoNo;

    novoNo = criarNo(src);
    novoNo->prox = grafo->lista[dest].cabeca;
    grafo->lista[dest].cabeca = novoNo;
}

void DFS(Grafo* grafo, int vertice) {
    No* adjList = grafo->lista[vertice].cabeca;
    No* temp = adjList;

    grafo->visitado[vertice] = 1;
    printf("Visitado %d \n", vertice);

    while (temp != NULL) {
        int conectadoVertice = temp->vertice;

        if (grafo->visitado[conectadoVertice] == 0) {
            DFS(grafo, conectadoVertice);
        }
        temp = temp->prox;
    }
}

int main() {
    int vertices = 5;
    Grafo* grafo = criarGrafo(vertices);

    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 4);
    adicionarAresta(grafo, 1, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 1, 4);
    adicionarAresta(grafo, 2, 3);
    adicionarAresta(grafo, 3, 4);

    printf("Busca em profundidade a partir do vértice 0:\n");
    DFS(grafo, 0);

    return 0;
}
