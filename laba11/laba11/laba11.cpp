#include <iostream>
#include <ctime>

using namespace std;

bool firstAlgorithm(int* room)
{
    bool found = true;
    int box;
    for (int i = 1; i <= 100; i++) {
        found = false;
        box = i;
        for (int j = 0; j < 50; j++) {
            if (room[box - 1] == i) {
                found = true;
                break;
            }
            box = room[box - 1];
        }
        if (!found) {
            break;
        }
    }
    return found;
}

bool secondAlgorithm(int* room)
{
    bool found = true;
    for (int i = 1; i <= 100; i++) {
        bool visited[100] = { false };
        found = false;
        for (int j = 0; j < 50; j++) {
            int index;
            while (true) {
                index = rand() % 100;
                if (!visited[index]) {
                    visited[index] = true;
                    break;
                }
            }
            if (room[index] == i) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return found;
}

void sortedNumber(int* arr, int size)
{
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int N;
    while (true) {
        cout << "¬ведите количество раундов сравнений: ";
        cin >> N;
        if (N <= 0) {
            cout << "¬ы ввели недопустимое значение" << endl;
            continue;
        }
        break;
    }

    int room[100];
    for (int i = 0; i < 100; i++) {
        room[i] = i + 1;
    }

    int countFirst = 0;
    int countSecond = 0;
    for (int i = 0; i < N; i++) {
        sortedNumber(room, 100);

        if (firstAlgorithm(room)) {
            countFirst++;
        }
        if (secondAlgorithm(room)) {
            countSecond++;
        }
    }

    cout << " оличество успешных исходов решени€ задачи случайным способом: " << countSecond << endl;
    cout << " оличество успешных исходов решени€ задачи способом выбора номера в коробке: " << countFirst << endl;

    return 0;
}
