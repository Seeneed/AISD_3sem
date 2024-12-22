#include <iostream>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    int N;

    while (true) {
        cout << "Введите количество городов: ";
        cin >> N;
        if (N <= 2) {
            cout << "Городов не может быть меньше 2!" << endl;
            continue;
        }
        break;
    }

    srand(time(0));
    int** arr = new int* [N];
    cout << "Матрица расстояний между городами: " << endl;
    for (int i = 0; i < N; i++) {
        arr[i] = new int[N];
        for (int j = 0; j < N; j++) {
            if (i == j) {
                arr[i][j] = INT_MAX;
            }
            else {
                arr[i][j] = rand() % 99 + 1;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] == INT_MAX) {
                cout << "INF ";
            }
            else {
                cout << arr[i][j] << " ";
            }
        }
        cout << endl;
    }

    double pheromone;
    int iterations, alpha, beta;

    while (true)
    {
        cout << "Введите количество феромонов на каждом ребре: ";
        cin >> pheromone;
        if (pheromone >= 1 || pheromone <= 0) {
            cout << "Значение феромонов не может быть меньше 0 или больше 1!" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Введите alpha: ";
        cin >> alpha;
        if (alpha < 1 || alpha > 4) {
            cout << "alpha имеет недопустимое значение!" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Введите beta: ";
        cin >> beta;
        if (beta < 1 || beta > 4) {
            cout << "beta имеет недопустимое значение!" << endl;
            continue;
        }
        break;
    }

    cout << "Введите количество итераций: ";
    cin >> iterations;

    double** pheromones = new double* [N];
    for (int i = 0; i < N; i++) {
        pheromones[i] = new double[N];
        for (int j = 0; j < N; j++) {
            pheromones[i][j] = pheromone;
        }
    }

    int bestDistance = INT_MAX;
    int* bestRoute = new int[N + 1];

    for (int it = 0; it < iterations; it++) {
        int** routes = new int* [N]; 
        int* distances = new int[N]; 

        for (int ant = 0; ant < N; ant++) {
            routes[ant] = new int[N + 1];
            bool* visited = new bool[N] { false };

            routes[ant][0] = ant;
            visited[ant] = true;

            for (int step = 1; step < N; step++) {
                int currentCity = routes[ant][step - 1];
                double totalProbability = 0.0;

                double* probabilities = new double[N];
                for (int nextCity = 0; nextCity < N; nextCity++) {
                    if (!visited[nextCity]) {
                        probabilities[nextCity] = pow(pheromones[currentCity][nextCity], alpha) *
                            pow(1.0 / arr[currentCity][nextCity], beta);
                        totalProbability += probabilities[nextCity];
                    }
                    else {
                        probabilities[nextCity] = 0;
                    }
                }

                double randomChoice = ((double)rand() / RAND_MAX) * totalProbability;
                double sum = 0.0;
                int nextCity = -1;
                for (int city = 0; city < N; city++) {
                    sum += probabilities[city];
                    if (randomChoice <= sum) {
                        nextCity = city;
                        break;
                    }
                }

                delete[] probabilities;

                routes[ant][step] = nextCity;
                visited[nextCity] = true;
            }

            routes[ant][N] = routes[ant][0];

            distances[ant] = 0;
            for (int i = 0; i < N; i++) {
                distances[ant] += arr[routes[ant][i]][routes[ant][i + 1]];
            }

            if (distances[ant] < bestDistance) {
                bestDistance = distances[ant];
                for (int i = 0; i <= N; i++) {
                    bestRoute[i] = routes[ant][i];
                }
            }

            delete[] visited;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                pheromones[i][j] *= 0.5;
            }
        }
        for (int ant = 0; ant < N; ant++) {
            for (int i = 0; i < N; i++) {
                int from = routes[ant][i];
                int to = routes[ant][i + 1];
                pheromones[from][to] += 1.0 / distances[ant];
                pheromones[to][from] += 1.0 / distances[ant];
            }
        }

        cout << "Итерация: " << it + 1;
        cout << "\nЛучший маршрут: ";
        for (int i = 0; i <= N; i++) {
            cout << bestRoute[i] + 1 << " ";
        }
        cout << "\nДлина маршрута: " << bestDistance << endl;

        for (int i = 0; i < N; i++) {
            delete[] routes[i];
        }
        delete[] routes;
        delete[] distances;
    }

    cout << "Итоговый лучший маршрут: ";
    for (int i = 0; i <= N; i++) {
        cout << bestRoute[i] + 1 << " ";
    }
    cout << "\nДлина итогового лучшего маршрута: " << bestDistance << endl;

    for (int i = 0; i < N; i++) {
        delete[] pheromones[i];
        delete[] arr[i];
    }
    delete[] pheromones;
    delete[] arr;
    delete[] bestRoute;

    return 0;
}
