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
