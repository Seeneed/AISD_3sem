#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int matrix[10][10] =
{
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};

void BFS_by_matrix(int start) {
    queue<int> q;
    bool visited[10] = { false };
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current + 1 << " ";
        for (int i = 0; i < 10; i++) {
            if (matrix[current][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

void DFS_by_matrix(int start) {
    stack<int> s;
    bool visited[10] = { false };
    s.push(start);
    visited[start] = true;
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current + 1 << " ";
        for (int i = 0; i < 10; i++) {
            if (matrix[current][i] == 1 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
}

int* list[10] = {
    new int[2] {2, 5},
    new int[3] {1, 7, 8},
    new int[1] {8},
    new int[2] {6, 9},
    new int[2] {1, 6},
    new int[3] {4, 5, 9},
    new int[2] {2, 8},
    new int[3] {2, 3, 7},
    new int[3] {4, 6, 10},
    new int[1] {9}
};

int sizes[10] = { 2, 3, 1, 2, 2, 3, 2, 3, 3, 1 };

void BFS_by_list(int start) {
    queue<int> q;
    bool visited[10] = { false };
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current + 1 << " ";
        for (int i = 0; i < sizes[current]; i++) {
            int near = list[current][i] - 1;
            if (!visited[near]) {
                q.push(near);
                visited[near] = true;
            }
        }
    }
}

void DFS_by_list(int start) {
    stack<int> s;
    bool visited[10] = { false };
    s.push(start);
    visited[start] = true;
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current + 1 << " ";
        for (int i = 0; i < sizes[current]; i++) {
            int near = list[current][i] - 1;
            if (!visited[near]) {
                s.push(near);
                visited[near] = true;
            }
        }
    }
}

struct Edge
{
    int start;
    int finish;
};

Edge edges[] = {
    {1, 2}, {1, 5},
    {2, 1}, {2, 7}, {2, 8},
    {3, 8},
    {4, 6}, {4, 9},
    {5, 1}, {5, 6},
    {6, 4}, {6, 5}, {6, 9},
    {7, 2}, {7, 8},
    {8, 2}, {8, 3}, {8, 7},
    {9, 4}, {9, 6}, {9, 10},
    {10, 9}
};

void BFS_by_edges(int start)
{
    queue<int> q;
    bool visited[10] = { false };
    q.push(start);
    visited[start - 1] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        for (Edge e : edges) {
            if (e.start == current && !visited[e.finish - 1]) {
                q.push(e.finish);
                visited[e.finish - 1] = true;
            }
            else if (e.finish == current && !visited[e.start - 1]) {
                q.push(e.start);
                visited[e.start - 1] = true;
            }
        }
    }
}

void DFS_by_edges(int start)
{
    stack<int> s;
    bool visited[10] = { false };
    s.push(start);
    visited[start - 1] = true; 
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current << " ";
        for (Edge e : edges) {
            if (e.start == current && !visited[e.finish - 1]) {
                s.push(e.finish);
                visited[e.finish - 1] = true;
            }
            else if (e.finish == current && !visited[e.start - 1]) {
                s.push(e.start);
                visited[e.start - 1] = true;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int start;
    cout << "Введите начальную вершину (1-10): ";
    cin >> start;
    if (start < 1 || start > 10) {
        cout << "Введите вершину в диапазоне от 1 до 10";
        return 1;
    }

    int v = 10, e = 11;
    cout << "Обход графа в ширину по матрице смежности: ";
    BFS_by_matrix(start - 1); 
    cout << endl;
    cout << "Обход графа в глубину по матрице смежности: ";
    DFS_by_matrix(start - 1);
    cout << endl;
    cout << "O большое для матрицы смежности: ";
    cout << pow(v, 2) << endl;
    cout << "Обход графа в ширину по списку смежности: ";
    BFS_by_list(start - 1);
    cout << endl;
    cout << "Обход графа в глубину по списку смежности: ";
    DFS_by_list(start - 1);
    cout << endl;
    cout << "O большое для списка смежности: ";
    cout << abs(v) + abs(e) << endl;
    cout << "Обход графа в ширину по списку рёбер: ";
    BFS_by_edges(start);
    cout << endl;
    cout << "Обход графа в глубину по списку рёбер: ";
    DFS_by_edges(start);
    cout << endl;
    cout << "O большое для списка рёбер: ";
    cout << abs(v) + abs(e) << endl;

    for (int i = 0; i < 10; i++) {
        delete[] list[i];
    }

    return 0;
}

