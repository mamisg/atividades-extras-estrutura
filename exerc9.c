#include <stdio.h>

void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > chave) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = chave;
        }
    }
}

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    shellSort(arr, n);

    imprimirArray(arr, n);

    return 0;
}
