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
} Grafo;

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->lista = (ListaAdj*)malloc(vertices * sizeof(ListaAdj));

    for (int i = 0; i < vertices; i++) {
        grafo->lista[i].cabeca = NULL;
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

void removerAresta(Grafo* grafo, int src, int dest) {
    No* temp = grafo->lista[src].cabeca;
    No* prev = NULL;

    while (temp != NULL && temp->vertice != dest) {
        prev = temp;
        temp = temp->prox;
    }

    if (temp != NULL) {
        if (prev != NULL) {
            prev->prox = temp->prox;
        } else {
            grafo->lista[src].cabeca = temp->prox;
        }
        free(temp);
    }

    temp = grafo->lista[dest].cabeca;
    prev = NULL;

    while (temp != NULL && temp->vertice != src) {
        prev = temp;
        temp = temp->prox;
    }

    if (temp != NULL) {
        if (prev != NULL) {
            prev->prox = temp->prox;
        } else {
            grafo->lista[dest].cabeca = temp->prox;
        }
        free(temp);
    }
}

void imprimirGrafo(Grafo* grafo) {
    for (int v = 0; v < grafo->numVertices; v++) {
        No* temp = grafo->lista[v].cabeca;
        printf("\n Lista de adjacência do vértice %d\n ", v);
        while (temp) {
            printf("-> %d", temp->vertice);
            temp = temp->prox;
        }
        printf("\n");
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

    imprimirGrafo(grafo);

    printf("\nRemovendo aresta entre 1 e 4\n");
    removerAresta(grafo, 1, 4);
    imprimirGrafo(grafo);

    return 0;
}
