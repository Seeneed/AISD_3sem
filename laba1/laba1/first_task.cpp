#include <iostream>
#include <Windows.h>
#include <chrono>

using namespace std;
using namespace chrono;

int steps_count = 0;

void hanoi_tower(int N, int begin_stick, int mid_stick, int end_stick)
{
    if (N > 1) {
        hanoi_tower(N - 1, begin_stick, end_stick, mid_stick);
        cout << "Переместить диск " << N << " со стержня " << begin_stick << " на стержень " << end_stick << endl;
        steps_count++;
        hanoi_tower(N - 1, mid_stick, begin_stick, end_stick);
    }
    else {
        cout << "Переместить диск 1 со стержня " << begin_stick << " на стержень " << end_stick << endl;
        steps_count++;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    int N, k, start_stick;
    cout << "Введите количество дисков: ";
    cin >> N;
    cout << "Введите количество стержней: ";
    cin >> k;
    cout << "Введите начальный стержень (1, 2 или 3): ";
    cin >> start_stick;

    if (k < 3 || k > 3) {
        cout << "Стержней не может быть меньше и больше 3" << endl;
        return 1;
    }
    if (N < 1) {
        cout << "Дисков не может быть меньше 1" << endl;
    }
    if (start_stick < 1 || start_stick > 3) {
        cout << "Стартовый стержень может быть только 1, 2 или 3" << endl;
    }
    else {
        int end_stick = 6 - start_stick - (start_stick == 3 ? 1 : 3);
        int mid_stick = 6 - start_stick - end_stick;
        auto start = high_resolution_clock::now();
        hanoi_tower(N, start_stick, mid_stick, end_stick);
        auto end = high_resolution_clock::now();
        auto different = duration_cast<milliseconds>(end - start);
        cout << "Время выполнения: " << different.count() << " миллисекунд" << endl;
        cout << "Количество ходов: " << steps_count << endl;
    }
    return 0;
}
