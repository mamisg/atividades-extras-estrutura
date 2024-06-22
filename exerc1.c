#include <stdio.h>
#include <stdlib.h>

#define MAX_INTERSECTIONS 100

void inicializarMatriz(int matriz[MAX_INTERSECTIONS][MAX_INTERSECTIONS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = 0;
        }
    }
}

void inserirRua(int matriz[MAX_INTERSECTIONS][MAX_INTERSECTIONS], int intersecao1, int intersecao2) {
    matriz[intersecao1][intersecao2] = 1;
    matriz[intersecao2][intersecao1] = 1;
}

void exibirMatriz(int matriz[MAX_INTERSECTIONS][MAX_INTERSECTIONS], int n) {
    printf("Matriz de Adjacências:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, intersecao1, intersecao2;
    int matriz[MAX_INTERSECTIONS][MAX_INTERSECTIONS];

    printf("Digite o número de interseções: ");
    scanf("%d", &n);

    if (n > MAX_INTERSECTIONS) {
        printf("Número máximo de interseções excedido.\n");
        return 1;
    }

    inicializarMatriz(matriz, n);

    int opcao;
    do {
        printf("\n1. Inserir nova rua\n");
        printf("2. Exibir matriz de adjacências\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite as interseções para conectar (0 a %d): ", n-1);
                scanf("%d %d", &intersecao1, &intersecao2);
                if (intersecao1 >= 0 && intersecao1 < n && intersecao2 >= 0 && intersecao2 < n) {
                    inserirRua(matriz, intersecao1, intersecao2);
                } else {
                    printf("Interseções inválidas.\n");
                }
                break;
            case 2:
                exibirMatriz(matriz, n);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(opcao != 3);

    return 0;
}
