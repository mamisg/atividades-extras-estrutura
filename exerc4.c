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

typedef struct Fila {
    int* itens;
    int frente;
    int tras;
    int capacidade;
} Fila;

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

Fila* criarFila(int capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->frente = fila->tras = -1;
    fila->itens = (int*)malloc(capacidade * sizeof(int));
    return fila;
}

int estaVazia(Fila* fila) {
    return fila->frente == -1;
}

int estaCheia(Fila* fila) {
    return fila->tras == fila->capacidade - 1;
}

void enfileirar(Fila* fila, int valor) {
    if (!estaCheia(fila)) {
        if (fila->frente == -1)
            fila->frente = 0;
        fila->tras++;
        fila->itens[fila->tras] = valor;
    }
}

int desenfileirar(Fila* fila) {
    int item;
    if (!estaVazia(fila)) {
        item = fila->itens[fila->frente];
        fila->frente++;
        if (fila->frente > fila->tras)
            fila->frente = fila->tras = -1;
        return item;
    }
    return -1;
}

void BFS(Grafo* grafo, int verticeInicial) {
    Fila* fila = criarFila(grafo->numVertices);

    grafo->visitado[verticeInicial] = 1;
    enfileirar(fila, verticeInicial);

    while (!estaVazia(fila)) {
        int verticeAtual = desenfileirar(fila);
        printf("Visitado %d \n", verticeAtual);

        No* temp = grafo->lista[verticeAtual].cabeca;

        while (temp) {
            int verticeAdj = temp->vertice;

            if (!grafo->visitado[verticeAdj]) {
                grafo->visitado[verticeAdj] = 1;
                enfileirar(fila, verticeAdj);
            }
            temp = temp->prox;
        }
    }

    free(fila->itens);
    free(fila);
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

    printf("Busca em largura a partir do vértice 0:\n");
    BFS(grafo, 0);

    free(grafo->visitado);
    for (int i = 0; i < vertices; i++) {
        No* temp = grafo->lista[i].cabeca;
        while (temp) {
            No* proximo = temp->prox;
            free(temp);
            temp = proximo;
        }
    }
    free(grafo->lista);
    free(grafo);

    return 0;
}
