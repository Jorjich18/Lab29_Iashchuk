#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

struct celebrating {
    char celebrate[77];
    char date[6];
};

void create_file(char* name)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutpuCP(CP_UTF8);
    FILE* f;
    char s[100];
    if (fopen_s(&f, name, "at+") != 0 || f == NULL) {
        cout << "Неможливо створити файл";
        return;
    }
    cout << "Введіть рядки такої структури:" << endl;
    cout << "Свято\tДата\n";
    do {
        cin.getline(s, 100);
        fputs(s, f);
        fputs("\n", f);
    } while (strcmp(s, ""));
    fclose(f);
}

void view_text_file(char* name) 
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutpuCP(CP_UTF8);
    celebrating z;
    FILE* f;
    char s[100];
    if (fopen_s(&f, name, "rt") != 0 || f == NULL) {
        cout << "Неможливо відкрити файл";
        return;
    }
    cout << "Перегляд файлу:\n" << endl;
    cout << "Свято\tДата\n";
    while (fgets(s, sizeof(s), f)) {
        if (sscanf(s, "%76s\t%5s", z.celebrate, z.date) == 2)
            printf("%s\t%s\n", z.celebrate, z.date);
    }
    fclose(f);
}

void select_nearest_winter_holiday(char* name)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutpuCP(CP_UTF8);
    celebrating z;
    FILE* f;
    char s[100];
    if (fopen_s(&f, name, "rt") != 0 || f == NULL) {
        cout << "Неможливо відкрити файл";
        return;
    }
    time_t t = time(NULL);
    struct tm* current_time = localtime(&t);
    int current_day = current_time->tm_mday;
    int current_month = current_time->tm_mon + 1;
    int min_days_to_holiday = 366;
    celebrating nearest_holiday;
    bool found = false;
    while (fgets(s, sizeof(s), f)) {
        if (sscanf(s, "%76s\t%5s", z.celebrate, z.date) == 2){
            int day, month;
            sscanf(z.date, "%d.%d", &day, &month);
            if (month == 12 || month == 1 || month == 2) {
                int days_to_holiday;
                if (month < current_month || (month == current_month && day < current_day))
                    days_to_holiday = 365 - ((current_month - month) * 30 + (current_day - day));
                else
                    days_to_holiday = (month - current_month) * 30 + (day - current_day);
                if (days_to_holiday < min_days_to_holiday) {
                    min_days_to_holiday = days_to_holiday;
                    nearest_holiday = z;
                    found = true;
                }
            }
        }
    }
    if (found) {
        cout << "\nНайближче зимове свято: ";
        cout << nearest_holiday.celebrate << " (" << nearest_holiday.date << ")" << endl;
    }
    else {
        cout << "Немає свят у списку.\n";
    }
    fclose(f);
}

int main() 
{
    system("color F0");
    char fn[] = "exersize.txt";
    create_file(fn);
    view_text_file(fn);
    select_nearest_winter_holiday(fn);
    system("pause");
    return 0;
}
