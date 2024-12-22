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
        cout << "����������� ���� " << N << " �� ������� " << begin_stick << " �� �������� " << end_stick << endl;
        steps_count++;
        hanoi_tower(N - 1, mid_stick, begin_stick, end_stick);
    }
    else {
        cout << "����������� ���� 1 �� ������� " << begin_stick << " �� �������� " << end_stick << endl;
        steps_count++;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    int N, k, start_stick;
    cout << "������� ���������� ������: ";
    cin >> N;
    cout << "������� ���������� ��������: ";
    cin >> k;
    cout << "������� ��������� �������� (1, 2 ��� 3): ";
    cin >> start_stick;

    if (k < 3 || k > 3) {
        cout << "�������� �� ����� ���� ������ � ������ 3" << endl;
        return 1;
    }
    if (N < 1) {
        cout << "������ �� ����� ���� ������ 1" << endl;
    }
    if (start_stick < 1 || start_stick > 3) {
        cout << "��������� �������� ����� ���� ������ 1, 2 ��� 3" << endl;
    }
    else {
        int end_stick = 6 - start_stick - (start_stick == 3 ? 1 : 3);
        int mid_stick = 6 - start_stick - end_stick;
        auto start = high_resolution_clock::now();
        hanoi_tower(N, start_stick, mid_stick, end_stick);
        auto end = high_resolution_clock::now();
        auto different = duration_cast<milliseconds>(end - start);
        cout << "����� ����������: " << different.count() << " �����������" << endl;
        cout << "���������� �����: " << steps_count << endl;
    }
    return 0;
}
