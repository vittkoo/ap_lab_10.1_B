#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialnist { COMPUTER_SCIENCE, INFORMATICS, MATH_AND_ECONOMICS, PHYSICS_AND_INFORMATICS, LABOR_TRAINING };

string specialnistStr[] = {
    "��������� �����",
    "�����������",
    "���������� �� ��������",
    "Գ���� �� �����������",
    "������� ��������"
};

struct Student {
    string prizv;
    int kurs;
    Specialnist spec;
    int fizyka;
    int matematika;
    union {
        int programuvannia;
        int chyselni_metody;
        int pedahohika;
    };
};

void Create(Student* students, const int N);
void Print(const Student* students, const int N);
void PrintAverages(const Student* students, const int N);
double PercentHighPhysics(const Student* students, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* students = new Student[N];

    Create(students, N);
    Print(students, N);
    PrintAverages(students, N);

    double percent = PercentHighPhysics(students, N);
    cout << "������� �������� � �������� 4 ��� 5 � ������: "
        << fixed << setprecision(2) << percent << "%" << endl;

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;

        cin.ignore();
        cout << "    �������: ";
        getline(cin, students[i].prizv);

        cout << "    ���� (1-4): "; cin >> students[i].kurs;

        cout << "    ������������ (0 - ��������� �����, 1 - �����������, "
            << "2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> spec;
        students[i].spec = (Specialnist)spec;

        cout << "    ������ � ������: "; cin >> students[i].fizyka;

        cout << "    ������ � ����������: "; cin >> students[i].matematika;

        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << "    ������ � �������������: ";
            cin >> students[i].programuvannia;
        }
        else if (students[i].spec == INFORMATICS) {
            cout << "    ������ � ��������� ������: ";
            cin >> students[i].chyselni_metody;
        }
        else {
            cout << "    ������ � ���������: ";
            cin >> students[i].pedahohika;
        }
        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "====================================================================================================================" << endl;
    cout << "| �  | �������       | ���� | ������������            | Գ���� | ���������� | �������. | ����. ���. | ��������� |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " "
             << "| " << setw(15) << left << students[i].prizv
             << "| " << setw(4) << left << students[i].kurs << " "
             << "| " << setw(25) << left << specialnistStr[students[i].spec]
             << "| " << setw(7) << right << students[i].fizyka
             << "| " << setw(11) << right << students[i].matematika;

        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << "| " << setw(9) << right << students[i].programuvannia
                 << "| " << setw(11) << right << "-"
                 << "| " << setw(11) << right << "-" << " |" << endl;
        }
        else if (students[i].spec == INFORMATICS) {
            cout << "| " << setw(9) << right << "-"
                 << "| " << setw(11) << right << students[i].chyselni_metody
                 << "| " << setw(11) << right << "-" << " |" << endl;
        }
        else {
        cout << "| " << setw(9) << right << "-"
             << "| " << setw(11) << right << "-"
             << "| " << setw(11) << right << students[i].pedahohika << " |" << endl;
        }
    }

    cout << "====================================================================================================================" << endl;
}

void PrintAverages(const Student* students, const int N) {
    cout << "������ ���� ��������:" << endl;
    for (int i = 0; i < N; i++) {
        double avg;
        if (students[i].spec == COMPUTER_SCIENCE) {
            avg = (students[i].fizyka + students[i].matematika + students[i].programuvannia) / 3.0;
        }
        else if (students[i].spec == INFORMATICS) {
            avg = (students[i].fizyka + students[i].matematika + students[i].chyselni_metody) / 3.0;
        }
        else {
            avg = (students[i].fizyka + students[i].matematika + students[i].pedahohika) / 3.0;
        }
        cout << setw(15) << left << students[i].prizv
            << ": " << fixed << setprecision(2) << avg << endl;
    }
}

double PercentHighPhysics(const Student* students, const int N) {
    int count = 0, total = 0;

    for (int i = 0; i < N; i++) {
        if (students[i].fizyka >= 4) {
            count++;
        }
        total++;
    }

    return (total > 0) ? (100.0 * count / total) : 0.0;
}