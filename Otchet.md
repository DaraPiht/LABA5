МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №5<br/> по дисциплине "Программирование"
<br/>

студентки 1 курса группы ПИ-б-о-191(1)  
Пихтиенко Дарьи Владиславовны
направления подготовки 09.03.04 "Программная инженерия"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2020

## Лабораторная работа №5
Работа с текстовыми файлами\
\
**Цель:** 
Научиться работать с текстовыми файлами и закрепить навыки работы со структурами.
\
**Ход работы:**\
**1\.** Из [папки](https://github.com/rebeccabilbro/titanic/tree/master/data) на GitHub скачиваем файл train.csv, хранящий информацию о пасажирах титаника.\
**2\.** На основании файла data_dictionary.txt создаем структуру для чтения записей из файла train.csv.\
**3\.** Пишем программу, считывающию данные из файла train.csv и сохранающию в новый [файл](https://github.com/DaraPiht/LABA5/blob/master/file.txt) результаты подсчета некоторых характеристик.\
Рассчитали и сохранили в новый файл следующие характеристики:
                
| Характеристика  | Результат |
| ------------- | ------------- |
| Общее число выживших | 342  |
| Число выживших из 1 класса  | 136  |
| Число выживших из 2 класса  | 87  |
| Число выживших из 3 класса  | 119  |
| Количество выживших женщин  | 233  |
| Количество выживших мужчин  | 109  |
| Средний возраст пассажира  | 28.3241  |
| Средний возраст мужчин  | 27.2366  |
|Средний возраст женщин  | 28.8376  |
|Штат, в котором село больше всего пассажиров | Southampton  |
                
Список идентификаторов несовершеннолетних пассажиров: 8, 10, 11, 15, 17, 23, 25, 40, 44, 51, 59, 60, 64, 69, 72, 79, 85, 87, 112, 115, 120, 126, 139, 148, 157, 164, 165, 166, 172, 173, 183, 184, 185, 194, 206, 209, 221, 234, 238, 262, 267, 279, 283, 298, 306, 308, 330, 334, 341, 349, 353, 375, 382, 387, 390, 408, 420, 434, 436, 446, 447, 449, 470, 480, 481, 490, 501, 505, 531, 533, 536, 542, 543, 550, 551, 575, 619, 635, 643, 645, 684, 687, 690, 692, 721, 722, 732, 747, 751, 752, 756, 765, 778, 781, 782, 788, 789, 792, 803, 804, 814, 820, 825, 828, 831, 832, 842, 845, 851, 853, 854, 870, 876.\
Код программы:
```c++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum Sex
{
    male,
    female
};

struct Passenger
{
   int id;
   bool survived;
   int p_class;
   string name;
   Sex sex;
   double age;
   short sibsp;
   short parch;
   string ticket;
   double fare;
   string cabin;
   char embarked;
};

vector<Passenger> passengers;
vector<int> underage;
   int lp = 0;
string reading(string ss, string d)
{
    int begin = lp;
    int end = ss.find(d, begin);

    lp = end + d.size();

    return ss.substr(begin, end - begin);
}

int main()
{
    ifstream fin("C:/Users/acer/Documents/laba5/train.csv");

    string ss;

    //skip first string
    getline(fin, ss, '\r');

    while(getline(fin, ss, '\r'))
    {
        lp = 0;
        Passenger p;


        p.id = stoi(reading(ss, ","));
        p.survived = stoi(reading(ss, ","));
        p.p_class = stoi(reading(ss, ",\""));
        p.name = reading(ss, "\",");
        p.sex = reading(ss, ",") == "male" ? male : female;

        string age = (reading(ss, ","));
        if (age != "")
           p.age = stod(age);
        else
            p.age = -1;

        p.sibsp = stoi(reading(ss, ","));
        p.parch = stoi(reading(ss, ","));
        p.ticket = reading(ss, ",");
        p.fare = stod(reading(ss, ","));
        p.cabin = reading(ss, ",");
        p.embarked = reading(ss, " ")[0];

        if (p.age != -1 && p.age < 18)
            underage.push_back(p.id);

        passengers.push_back(p);
    }

    int alive_count = 0, alive_first = 0, alive_second = 0, alive_third = 0;
    int alive_female = 0, alive_male = 0;

    double age_everyone = 0; int count_everyone = 0;
    double age_female = 0; int count_female = 0;
    double age_male = 0; int count_male = 0;

    int embarked_c = 0; int embarked_q = 0; int embarked_s = 0;
    for (int i = 0; i < passengers.size(); i++)
    {
        Passenger p = passengers[i];
        if (p.survived)
        {
            alive_count++;
            if (p.p_class == 1)
                alive_first++;
            else if (p.p_class == 2)
                alive_second++;
            else if (p.p_class == 3)
                alive_third++;

            if (p.sex == male)
                alive_male++;
            else alive_female++;

        }

        if (p.age != -1)
        {
            age_everyone += p.age;
            count_everyone++;

            if (p.sex == male)
            {
                age_male += p.age;
                count_male++;
            }
            else
            {
                age_female += p.age;
                count_female++;
            }
        }

        switch (p.embarked)
        {
        case 'C':
            embarked_c++;
            break;
        case 'S':
            embarked_s++;
            break;
        case 'Q':
            embarked_q++;
            break;
        }
    }

    age_everyone /= count_everyone;
    age_female /= count_female;
    age_male /= count_male;

    int max_city = max(embarked_c, max(embarked_q, embarked_s));

    ofstream fout("C:/Users/acer/Documents/laba5/output.txt");

    fout << "Total alive count: " << alive_count << '\n';
    fout << "First-class survivors: " << alive_first << '\n';
    fout << "Second-class survivors: " << alive_second << '\n';
    fout << "Third-class survivors: " << alive_third << '\n';
    fout << "Female survived: " << alive_female << '\n';
    fout << "Male survived: " << alive_male << '\n';
    fout << "Average age: " << age_everyone << '\n';
    fout << "Average age(female): " << age_female << '\n';
    fout << "Average age(male): " << age_male << '\n';
    fout << "State with most passengers: ";

        if (max_city == embarked_c)
            fout << "Cherbourg" << '\n';
        if (max_city == embarked_q)
            fout << "Queenstown" << '\n';
        if (max_city == embarked_s)
            fout << "Southampton" << '\n';

    fout << "Ids of underage passengers: ";
        for (int i = 0; i < underage.size(); i++)
            fout << underage[i] << ", ";

    fin.close();
    fout.close();
    return 0;
}
```

\
**Вывод:** В ходе выполнения данной лабораторной работы я научилась работать с текстовыми файлами и закрепила навыки работы со структурами.
