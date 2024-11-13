#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Kurs { I = 1, II, III, IV, V, VI };
enum Spec { ME, MF, FI, INF, KN };

struct Student {
    string prizv;     
    int kurs;        
    Spec spec;       
    int mark_physics; 
    int mark_math;    
    int mark_informatics; 
};

void input_students(Student* students, int n);
void print_table(const Student* students, int n);
void sort_students(Student* students, int n);
int* create_index_array(const Student* students, int n);
void print_indexed_table(const Student* students, const int* index_array, int n);
int binary_search_student(const Student* students, int n, const string& prizv, int kurs, int third_mark_value);
string spec_to_string(Spec spec);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    cout << "������ ������� ��������: ";
    while (!(cin >> n) || n <= 0) {
        cout << "������ ��������. ���� �����, ������ ������� �����: ";
        cin.clear();
        cin.get();
        cin.sync();
    }

    Student* students = new Student[n];
    int* index_array = nullptr;
    int menu_option;

    do {
        cout << "\n����:\n";
        cout << "1 - ������ ��������\n";
        cout << "2 - ³��������� �������\n";
        cout << "3 - ��������� �������� (�� �������� ��������)\n";
        cout << "4 - ³��������� ����������� �������\n";
        cout << "5 - �������� ����� ��������\n";
        cout << "0 - �����\n";
        cout << "��� ����: ";
        cin >> menu_option;

        cin.get(); 
        cin.sync();

        switch (menu_option) {
        case 1:
            input_students(students, n);
            break;
        case 2:
            print_table(students, n);
            break;
        case 3:
            sort_students(students, n);
            cout << "�������� ���������� �� �������� ��������.\n";
            break;
        case 4:
            if (index_array) {
                delete[] index_array;
            }
            index_array = create_index_array(students, n);
            print_indexed_table(students, index_array, n);
            delete[] index_array;
            break;
        case 5: {
            string prizv;
            int kurs, third_mark_value;
            cout << "������ ������� ��� ������: ";
            cin >> prizv;
            cout << "������ ����: ";
            cin >> kurs;
            cout << "������ ������ � �����������: ";
            cin >> third_mark_value;

            int result = binary_search_student(students, n, prizv, kurs, third_mark_value);
            if (result != -1) {
                cout << "�������� ��������: " << students[result].prizv << " (����: "
                    << students[result].kurs << ", ������ � �����������: "
                    << students[result].mark_informatics << ")\n";
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            cout << "����� � ��������.\n";
            break;
        default:
            cout << "������� ����. ���� �����, ������� ����� ���� �� ���.\n";
        }
    } while (menu_option != 0);

    delete[] students;
    return 0;
}

void input_students(Student* students, int n) {
    for (int i = 0; i < n; ++i) {
        cout << "������ ��� ��� �������� #" << (i + 1) << ":\n";
        cout << "�������: ";
        cin >> students[i].prizv;

        cout << "���� (1-6): ";
        while (!(cin >> students[i].kurs) || students[i].kurs < 1 || students[i].kurs > 6) {
            cout << "������ ��������. ������ ����� ����� �� 1 �� 6: ";
            cin.clear();
            cin.get();
            cin.sync(); 
        }

        int spec;
        cout << "������������ (0 - ME, 1 - MF, 2 - FI, 3 - INF, 4 - KN): ";
        while (!(cin >> spec) || spec < 0 || spec > 4) {
            cout << "������ ��������. ������ ����� �� 0 �� 4: ";
            cin.clear();
            cin.get(); 
            cin.sync(); 
        }
        students[i].spec = static_cast<Spec>(spec);

        cout << "������ � ������: ";
        while (!(cin >> students[i].mark_physics) || students[i].mark_physics < 0 || students[i].mark_physics > 5) {
            cout << "������ ��������. ������ ������ �� 0 �� 5: ";
            cin.clear();
            cin.get();
            cin.sync();
        }

        cout << "������ � ����������: ";
        while (!(cin >> students[i].mark_math) || students[i].mark_math < 0 || students[i].mark_math > 5) {
            cout << "������ ��������. ������ ������ �� 0 �� 5: ";
            cin.clear();
            cin.get();
            cin.sync();
        }

        cout << "������ � �����������: ";
        while (!(cin >> students[i].mark_informatics) || students[i].mark_informatics < 0 || students[i].mark_informatics > 5) {
            cout << "������ ��������. ������ ������ �� 0 �� 5: ";
            cin.clear();
            cin.get();
            cin.sync();
        }
    }
}

void print_table(const Student* students, int n) {
    cout << "------------------------------------------------------------------------------\n";
    cout << "| �  |   Surname   | Course |    Speciality    | Physics | Math | Informatics |\n";
    cout << "------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(2) << (i + 1) << "    | "
            << setw(10) << left << students[i].prizv << " | "
            << setw(6) << right << students[i].kurs << " | "
            << setw(15) << left << spec_to_string(students[i].spec)
            << " | " << setw(7) << students[i].mark_physics
            << " | " << setw(4) << students[i].mark_math
            << " | " << setw(10) << students[i].mark_informatics << " |\n";
    }
    cout << "------------------------------------------------------------------------------\n";
}

void sort_students(Student* students, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if ((students[j].mark_informatics < students[j + 1].mark_informatics) ||
                (students[j].mark_informatics == students[j + 1].mark_informatics &&
                    students[j].kurs < students[j + 1].kurs) ||
                (students[j].mark_informatics == students[j + 1].mark_informatics &&
                    students[j].kurs == students[j + 1].kurs &&
                    students[j].prizv > students[j + 1].prizv)) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

int* create_index_array(const Student* students, int n) {
    int* index_array = new int[n];
    for (int i = 0; i < n; ++i) {
        index_array[i] = i;
    }

    for (int i = 1; i < n; ++i) {
        int temp = index_array[i];
        int j = i - 1;

        while (j >= 0 &&
            ((students[index_array[j]].mark_informatics < students[temp].mark_informatics) ||
                (students[index_array[j]].mark_informatics == students[temp].mark_informatics &&
                    students[index_array[j]].kurs < students[temp].kurs) ||
                (students[index_array[j]].mark_informatics == students[temp].mark_informatics &&
                    students[index_array[j]].kurs == students[temp].kurs &&
                    students[index_array[j]].prizv < students[temp].prizv))) {
            index_array[j + 1] = index_array[j];
            j--;
        }
        index_array[j + 1] = temp;
    }

    return index_array;
}

void print_indexed_table(const Student* students, const int* index_array, int n) {
    cout << "------------------------------------------------------------------------------\n";
    cout << "| �  |   Surname   | Course |    Speciality    | Physics | Math | Informatics |\n";
    cout << "------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        int idx = index_array[i];
        cout << "| " << setw(2) << (i + 1) << "    | "
            << setw(10) << left << students[idx].prizv << " | "
            << setw(6) << right << students[idx].kurs << " | "
            << setw(15) << left << spec_to_string(students[idx].spec)
            << " | " << setw(7) << students[idx].mark_physics
            << " | " << setw(4) << students[idx].mark_math
            << " | " << setw(10) << students[idx].mark_informatics << " |\n";
    }
    cout << "-------------------------------------------------------------------------\n";
}

int binary_search_student(const Student* students, int n, const string& prizv, int kurs, int third_mark_value) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (students[mid].prizv == prizv &&
            students[mid].kurs == kurs &&
            students[mid].mark_informatics == third_mark_value) {
            return mid;
        }

        if ((students[mid].mark_informatics < third_mark_value) ||
            (students[mid].mark_informatics == third_mark_value && students[mid].kurs < kurs) ||
            (students[mid].mark_informatics == third_mark_value && students[mid].kurs == kurs && students[mid].prizv < prizv)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

string spec_to_string(Spec spec) {
    switch (spec) {
    case ME: return "Math & Econ";
    case MF: return "Labour Ed";
    case FI: return "Phys & Info";
    case INF: return "Informatics";
    case KN: return "Comp Sci";
    default: return "Unknown";
    }
}
