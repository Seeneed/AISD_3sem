#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);

    int N;
    cout << "������� ����������� �������: ";
    cin >> N;

    int valueOfProducts;
    cout << "������� ���������� �������: ";
    cin >> valueOfProducts;

    string* nameProduct = new string[valueOfProducts];
    int* weightProduct = new int[valueOfProducts];
    int* priceProduct = new int[valueOfProducts];

    for (int i = 0; i < valueOfProducts; i++) {
        cout << "������� �������� " << i + 1 << " ������: ";
        cin >> nameProduct[i];
        cout << "������� ��� " << i + 1 << " ������: ";
        cin >> weightProduct[i];
        cout << "������� ���� " << i + 1 << " ������: ";
        cin >> priceProduct[i];
    }

    int** arr = new int* [valueOfProducts + 1];
    for (int i = 0; i <= valueOfProducts; i++) {
        arr[i] = new int[N + 1];
    }

    for (int i = 0; i <= valueOfProducts; i++) {
        for (int j = 0; j <= N; j++) {
            if (i == 0 || j == 0) {
                arr[i][j] = 0;
            }
            else if (weightProduct[i - 1] <= j) {
                arr[i][j] = max(priceProduct[i - 1] + arr[i - 1][j - weightProduct[i - 1]], arr[i - 1][j]);
            }
            else {
                arr[i][j] = arr[i - 1][j];
            }
        }
    }
    cout << "\n������������ ��������� �������: " << arr[valueOfProducts][N] << endl;

    int totalweight = 0;
    int n = N;
    cout << "������ ���������� � ������: " << endl;
    for (int i = valueOfProducts; i > 0 && n > 0; i--) {
        if (arr[i][n] != arr[i - 1][n]) {
            cout << nameProduct[i - 1] << ", ����: " << priceProduct[i - 1] << ", ���: " << weightProduct[i - 1] << endl;
            totalweight += weightProduct[i - 1];
            n -= weightProduct[i - 1];
        }
    }
    cout << "��� �������, � ������ ���������� ���������: " << totalweight;

    for (int i = 0; i <= valueOfProducts; i++) {
        delete[] arr[i];
    }

    delete[] nameProduct;
    delete[] weightProduct;
    delete[] priceProduct;

    return 0;
}