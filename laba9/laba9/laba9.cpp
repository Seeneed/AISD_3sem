#include <iostream>
#include <string>
#include <climits>
#include <cstdlib>

using namespace std;

int N = 8;

void printGraph(int**& graph)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (graph[i][j] == INT_MAX) {
                cout << "INF ";
            }
            else {
                cout << graph[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void addCity(int**& graph)
{

    if (N == 9)
    {
        cout << "Количество городов не может быть больше 9!" << endl;
        return;
    }
    N++;
    int** newGraph = new int* [N];
    for (int i = 0; i < N; i++)
    {
        newGraph[i] = new int[N];
    }

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            newGraph[i][j] = graph[i][j];
        }
    }
    cout << endl;
    cout << "Введите расстояния от нового города к каждому из существующих городов:" << endl;
    for (int i = 0; i < N - 1; ++i)
    {
        cout << "Расстояние от нового города к городу " << i + 1 << ": ";
        cin >> newGraph[N - 1][i];
    }
    cout << endl;

    cout << "Введите расстояния от каждого из существующих городов к новому городу:" << endl;
    for (int i = 0; i < N - 1; i++)
    {
        cout << "Расстояние от города " << i + 1 << " к новому городу: ";
        cin >> newGraph[i][N - 1];
    }
    cout << endl;

    newGraph[N - 1][N - 1] = INT_MAX;

    for (int i = 0; i < N - 1; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;

    graph = newGraph;


    printGraph(graph);
}

void deleteCity(int**& graph)
{
    if (N == 8)
    {
        cout << "Количество городов не может быть меньше 8!" << endl;
        return;
    }

    int ind = 0;

    while (true)
    {
        cout << "Введите номер удаляемого города: ";
        cin >> ind;
        if (ind <= 0 || ind > N)
        {
            cout << "Введён неверный индекс!" << endl;
            continue;
        }
        break;
    }
    ind--;
    int** newGraph = new int* [N - 1];
    for (int i = 0; i < N - 1; ++i) {
        newGraph[i] = new int[N - 1];
    }

    for (int i = 0, newI = 0; i < N; i++)
    {
        if (i == ind) continue;
        for (int j = 0, newJ = 0; j < N; j++)
        {
            if (j == ind) continue;
            newGraph[newI][newJ] = graph[i][j];
            ++newJ;
        }
        ++newI;
    }

    for (int i = 0; i < N; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;

    graph = newGraph;
    N--;

    printGraph(graph);

}

struct individual
{
    string chromosome;
    int fitness;
};

bool repeat(string s, char ch)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ch)
            return true;
    }
    return false;
}

int random(int min, int max)
{
    return min + rand() % (max - min + 1);
}

string createChromo()
{
    string chromosome = "1";
    while (true) {
        if (chromosome.length() == N) {
            chromosome += chromosome[0];
            break;
        }
        int temp = random(1, N);
        if (!repeat(chromosome, (char)(temp + '0')))
            chromosome += (char)(temp + '0');
    }
    return chromosome;
}

string mutation(string chromo)
{
    while (true) {
        int gen1 = random(1, N);
        int gen2 = random(1, N);
        if (gen1 != gen2) {
            char temp = chromo[gen1];
            chromo[gen1] = chromo[gen2];
            chromo[gen2] = temp;
            break;
        }
    }
    return chromo;
}

int findFitness(string chromosome, int**& graph) {
    int f = 0;
    for (int i = 0; i < chromosome.length() - 1; i++) {
        int from = chromosome[i] - '1';
        int to = chromosome[i + 1] - '1';
        if (graph[from][to] == INT_MAX)
            return INT_MAX;

        f += graph[from][to];
    }
    return f;
}

void bubbleSort(individual* population, int populationSize)
{
    for (int i = 0; i < populationSize - 1; i++)
    {
        for (int j = 0; j < populationSize - i - 1; j++)
        {
            if (population[j].fitness > population[j + 1].fitness)
            {
                individual temp = population[j];
                population[j] = population[j + 1];
                population[j + 1] = temp;
            }
        }
    }
}

bool wasFirst = false;

string createChild(string parent1, string parent2)
{
    int point = random(1, N - 2);
    string chromo;
    if (!wasFirst)
    {
        chromo = parent1.substr(0, point);

        for (char gene : parent2)
        {
            if (chromo.find(gene) == string::npos)
            {
                chromo += gene;
            }
        }
        wasFirst = true;
    }
    else {
        chromo = parent2.substr(0, point);

        for (char gene : parent1)
        {
            if (chromo.find(gene) == string::npos)
            {
                chromo += gene;
            }
        }
        wasFirst = false;
    }
    chromo += chromo[0];
    return chromo;
}

void runGenetic(int**& graph, int populationSize, int childCount, int evolutionCount, int mutationPercent, int crossCount)
{
    int generationCount = 1;
    int premStop = 0;

    individual* population = new individual[populationSize];

    for (int i = 0; i < populationSize; i++)
    {
        individual buf;
        buf.chromosome = createChromo();
        buf.fitness = findFitness(buf.chromosome, graph);
        population[i] = buf;
    }
    cout << "Начальная популяция" << endl;
    cout << "Хромосома" << "-------" << "Приспособленность" << endl;
    for (int i = 0; i < populationSize; i++)
    {
        cout << population[i].chromosome << "\t" << population[i].fitness << endl;
    }
    cout << endl;

    bubbleSort(population, populationSize);

    string best = population[0].chromosome;

    for (int i = 0; i < evolutionCount, premStop < 25; i++)
    {

        if (best != population[0].chromosome)
        {
            best = population[0].chromosome;
            premStop = 0;
        }

        cout << endl << "Поколение " << generationCount++ << endl;
        cout << "Лучшая хромосома: " << population[0].chromosome << ", c приспособленностью: " << population[0].fitness << endl;

        individual* newPopulation = new individual[populationSize + crossCount * childCount];
        int ind = 0;
        for (ind = 0; ind < populationSize; ind++)
        {
            newPopulation[ind] = population[ind];
        }

        for (int j = 0; j < crossCount; j++)
        {
            while (true) {
                int parent1 = random(0, populationSize - 1);
                int parent2 = random(0, populationSize - 1);
                if (parent1 != parent2)
                {
                    for (int k = 0; k < childCount; k++)
                    {
                        string chromo = createChild(population[parent1].chromosome, population[parent2].chromosome);
                        int percent = random(0, 100);
                        if (mutationPercent <= percent)
                        {
                            chromo = mutation(chromo);
                        }

                        int fitness = findFitness(chromo, graph);
                        individual buf;
                        buf.chromosome = chromo;
                        buf.fitness = fitness;
                        newPopulation[ind++] = buf;
                    }

                    break;
                }
            }
        }
        bubbleSort(newPopulation, ind);
        for (int j = 0; j < populationSize; j++)
        {
            population[j] = newPopulation[j];
        }

        premStop++;
    }
    cout << endl << "Самая лучшая хромосома обнаруженная алгоритмом: " << population[0].chromosome << ", c приспособленностью: " << population[0].fitness << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    int populationSize;

    const int n = 8;

    srand(time(0));
    int gr[n][n] = {
      {INT_MAX, 25, 40, 31, 27,13,56,9},
      {5, INT_MAX, 17, 30, 25,6,9,34},
      {19, 15, INT_MAX, 6, 9, 23, 8, 19},
      {9, 50, 24, INT_MAX, 6, 24,14,9},
      {22, 8, 7, 10, INT_MAX, 9, 18, 6},
      {14, 18,23,40,21, INT_MAX, 23,67},
      {25, 12, 34, 9, 12, 5, INT_MAX, 18},
      {16, 12, 19, 27, 28, 31, 9, INT_MAX}
    };

    int** graph = new int* [N];
    for (int i = 0; i < N; ++i) {
        graph[i] = new int[N];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            graph[i][j] = gr[i][j];
        }
    }

    while (true)
    {
        cout << "Введите размер популяции: ";
        cin >> populationSize;
        if (populationSize < 2)
        {
            cout << "Популяция не может быть меньше 2!" << endl;
            continue;
        }
        break;
    }

    printGraph(graph);

    int answer = 0;
    while (true)
    {
        cout << "Вы хотите изменить начальный граф? (0 - нет, 1 - да): ";
        cin >> answer;
        if (answer < 0 || answer>1)
        {
            cout << "Вы ввели неправильное значение!" << endl;
            continue;
        }
        break;
    }

    if (answer)
    {
        while (true)
        {
            int choice = 0;
            cout << endl;
            cout << "Что вы хотите сделать?" << endl;
            cout << "1 - добавить город" << endl;
            cout << "2 - удалить город" << endl;
            cout << "0 - выход" << endl;
            cout << endl;
            cin >> choice;
            if (choice == 0)
            {
                break;
            }
            switch (choice)
            {
            case 1:
                addCity(graph);
                break;
            case 2:
                deleteCity(graph);
                break;
            case 3:
                break;
            default:
                cout << "Вы ввели неправильное значение" << endl;
            }
        }
    }

    int childCount;
    while (true)
    {
        cout << "Введите количество потомков при одном скрещивании: ";
        cin >> childCount;

        if (childCount < 1)
        {
            cout << "Количество потомков не может быть меньше 1!" << endl;
            continue;
        }
        break;
    }

    int crossCount;
    while (true)
    {
        cout << "Введите количество скрещиваний: ";
        cin >> crossCount;
        if (crossCount < 1)
        {
            cout << "Количество скрещиваний не может быть меньше 1!" << endl;
            continue;
        }
        break;
    }

    int evolutionCount = 0;
    while (true)
    {
        cout << "Введите количество эволюций: ";
        cin >> evolutionCount;
        if (evolutionCount < 0)
        {
            cout << "Количество эволюций не может быть меньше 0!" << endl;
            continue;
        }
        break;
    }

    int mutationPercent;
    while (true)
    {
        cout << "Введите показатель по мутации: ";
        cin >> mutationPercent;
        if (mutationPercent < 0 || mutationPercent > 100)
        {
            cout << "Показатель по мутации должен находится в пределах от 0 до 100!" << endl;
            continue;
        }
        break;
    }

    runGenetic(graph, populationSize, childCount, evolutionCount, mutationPercent, crossCount);
    return 0;
}
