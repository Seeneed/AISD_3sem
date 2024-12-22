#include <iostream>
#include <climits>

using namespace std;

int graph[9][9] = {
        {0, 7, 10, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 9, 27, 0, 0},
        {10, 0, 0, 0, 31, 8, 0, 0, 0},
        {0, 0, 0, 0, 32, 0, 0, 17, 21},
        {0, 0, 31, 32, 0, 0, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 11, 0},
        {0, 27, 0, 0, 0, 0, 0, 0, 15},
        {0, 0, 0, 17, 0, 11, 0, 0, 15},
        {0, 0, 0, 21, 0, 0, 15, 15, 0}
};

int getIndex(char letter) {
    return letter  - 'A';
}

void dijkstra(int graph[9][9], int start) {
    int distantion[9];
    bool visited[9] = { false };
    for (int i = 0; i < 9; i++) {
        distantion[i] = INT_MAX;
    }
    distantion[start] = 0;
    for (int i = 0; i < 9; i++) {
        int minDistantion = INT_MAX;
        int minIndex = -1;
        for (int j = 0; j < 9; j++) {
            if (!visited[j] && distantion[j] < minDistantion) {
                minDistantion = distantion[j];
                minIndex = j;
            }
        }
        visited[minIndex] = true;
        for (int j = 0; j < 9; j++) {
            if (graph[minIndex][j] && !visited[j] && distantion[minIndex] != INT_MAX && distantion[minIndex] + graph[minIndex][j] < distantion[j]) {
                distantion[j] = distantion[minIndex] + graph[minIndex][j];
            }
        }
    }
    cout << "Кратчайшие расстояния от вершины " << char(start + 'A') << ":" << endl;
    for (int i = 0; i < 9; i++) {
        cout << char(i + 'A') << ": " << distantion[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    bool isValidInput = false;
    char symbol[2];
    cout << "Введите стартовую вершину: ";
    while (!isValidInput) {
        cin >> symbol;
        if (symbol[0] >= 'A' && symbol[0] <= 'I') {
            isValidInput = true;
        }
        else {
            cout << "Некорректно введен символ, повторите попытку" << endl;
        }
    }
    int start = getIndex(symbol[0]);
    dijkstra(graph, start);
    return 0;
}
