#include <iostream>
using namespace std;

int Lis(int N, int arr[], int lis[], int prev[])
{
    if (N == 0) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        lis[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1; 
                prev[i] = j;
            }
        }
    }

    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < N; i++) {
        if (max < lis[i]) {
            max = lis[i];
            maxIndex = i;
        }
    }
    cout << "Длина максимальной подпоследовательности: " << max << endl;
    cout << "Максимальная подпоследовательность: ";
    int* result = new int[max];
    int index = max - 1;
    for (int i = maxIndex; i != -1; i = prev[i]) {
        result[index--] = arr[i];
    }
    for (int i = 0; i < max; i++) {
        cout << result[i] << " ";
    }
    delete[] result;
}

int main()
{
    setlocale(LC_ALL, "RU");
    int N;
    cout << "Введите число элементов последовательности: ";
    cin >> N;
    int* arr = new int[N];
    int* lis = new int[N];
    int* prev = new int[N]; 
    cout << "Введите элементы последовательности: ";
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    cout << "Исходная последовательность: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    Lis(N, arr, lis, prev); 
    delete[] arr;
    delete[] lis;
    delete[] prev;
    return 0;
}
