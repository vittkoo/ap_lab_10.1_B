#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialnist { COMPUTER_SCIENCE, INFORMATICS, MATH_AND_ECONOMICS, PHYSICS_AND_INFORMATICS, LABOR_TRAINING };

string specialnistStr[] = {
    "Комп’ютерні науки",
    "Інформатика",
    "Математика та економіка",
    "Фізика та інформатика",
    "Трудове навчання"
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
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];

    Create(students, N);
    Print(students, N);
    PrintAverages(students, N);

    double percent = PercentHighPhysics(students, N);
    cout << "Процент студентів з оцінками 4 або 5 з фізики: "
        << fixed << setprecision(2) << percent << "%" << endl;

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.ignore();
        cout << "    Прізвище: ";
        getline(cin, students[i].prizv);

        cout << "    Курс (1-4): "; cin >> students[i].kurs;

        cout << "    Спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, "
            << "2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        students[i].spec = (Specialnist)spec;

        cout << "    Оцінка з фізики: "; cin >> students[i].fizyka;

        cout << "    Оцінка з математики: "; cin >> students[i].matematika;

        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << "    Оцінка з програмування: ";
            cin >> students[i].programuvannia;
        }
        else if (students[i].spec == INFORMATICS) {
            cout << "    Оцінка з чисельних методів: ";
            cin >> students[i].chyselni_metody;
        }
        else {
            cout << "    Оцінка з педагогіки: ";
            cin >> students[i].pedahohika;
        }
        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "====================================================================================================================" << endl;
    cout << "| №  | Прізвище       | Курс | Спеціальність            | Фізика | Математика | Програм. | Числ. мет. | Педагогіка |" << endl;
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
    cout << "Середні бали студентів:" << endl;
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