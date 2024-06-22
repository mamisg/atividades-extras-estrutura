#include <stdio.h>

void trocar(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int particionar(int arr[], int inicio, int fim) {
    int pivot = arr[fim]; // pivô é o último elemento
    int i = inicio - 1; // índice do menor elemento

    for (int j = inicio; j <= fim - 1; j++) {
        if (arr[j] < pivot) {
            i++; // incrementa o índice do menor elemento
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[fim]);
    return i + 1;
}

void quickSort(int arr[], int inicio, int fim) {
    if (inicio < fim) {
        int pi = particionar(arr, inicio, fim);

        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fim);
    }
}

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    imprimirArray(arr, tamanho);

    quickSort(arr, 0, tamanho - 1);

    printf("Array ordenado:\n");
    imprimirArray(arr, tamanho);

    return 0;
}
