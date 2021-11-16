#include "../lib/util.h"
#include "../lib/Patient.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

std::array<double, 11> fill_sample(Patient pt);

std::vector<Patient> load_patients(std::string filename)    {
    std::ifstream inFile(filename);
    std::vector<Patient> pt_data;

    bool male = false;
    short unsigned int age = 0;
    bool cond = false;
    bool hosp = false;
    char race = ' ';
    char current = ' ';

    inFile.ignore(36);
    while (inFile.eof() != true)
    {   
        inFile.get(current);        // Age
        if (current == '5')
        {
            inFile.get(current);
            if (current == '5')
            {
                age = 55;
                inFile.ignore();
            }
            else
            {
                age = 5;
            }
        }
        else
        {
            age = int(current - 48) * 10 + 5;
            inFile.ignore(2);
        }

        inFile.get(current);        // Sex
        if (current == 'm')
        {
            male = true;
        }
        else
        {
            male = false;
        }
        inFile.ignore();

        inFile.get(current);        // Race
        if (current == 'i' || current == 'W' || current == 'B' || current == 'A' || current == 'H' || current == 'N')
        {
            race = current;
            inFile.ignore();
        }
        else
        {
            continue;
            inFile.ignore(100, '\n');
        }

        inFile.get(current);        // Condition
        if (current == '1')
        {
            cond = true;
        }
        else if (current == '0')
        {
            cond = false;
        }
        else{
            continue;
        }
        inFile.ignore();

        inFile.get(current);
        if (current == '1')
        {
            hosp = true;
        }
        else
        {
            hosp = false;
        }
        inFile.ignore();
        pt_data.push_back(Patient(age, male, cond, hosp, race));
    }

    return pt_data;
}

std::array<std::vector<std::array<double, 11>>, 2> split(std::vector<Patient> data, double frac)
{
    srand(time(NULL));
    unsigned int n = data.size();
    unsigned int m = 0;
    std::array<std::vector<std::array<double, 11>>, 2> retList;
    std::vector<std::array<double, 11>> train;
    std::vector<std::array<double, 11>> test;
    std::array<double, 11> current;

    if (frac > 0 && frac <= 1)
    {
        m = int(frac * n);
    }
    else
    {
        std::cerr << "Error: split size of " << frac << " is not in range 0-1.";
    }

    for (unsigned int i = 0; i < n; i++)
    {
        if (i != n)
        {
            std::swap(data.at(i), data.at(rand() % data.size()));
        }
    }

    for (unsigned int i = 0; i < m; i++)
    {
        train.push_back(fill_sample(data.at(i)));
    }

    for (unsigned int i = m; i < n; i++)
    {
        test.push_back(fill_sample(data.at(i)));
    }

    retList.at(0) = train;
    retList.at(1) = test;

    return retList;
}

std::array<double, 11> fill_sample(Patient pt)
{   
    std::array<double, 11> retList;
    for (auto i = retList.begin(); i != retList.end(); i++)
    {
        *i = 0;
    }

    if (pt.getAge() < 0)        // Age
    {
        std::cerr << "Error: age is " << pt.getAge() << ". Age cannot be negative.";
        std::exit(0);
    }

    retList.at(0) = exp(0.03 * pt.getAge());

    if (pt.getMale() == true)       // Sex
    {
        retList.at(1) = 1;
    }
    else
    {
        retList.at(2) = 1;
    }

    switch (pt.getRace())       // Race
    {
        case 'i':
            retList.at(3) = 1;
            break;
        case 'W':
            retList.at(4) = 1;
            break;
        case 'B':
            retList.at(5) = 1;
            break;
        case 'A':
            retList.at(6) = 1;
            break;
        case 'H':
            retList.at(7) = 1;
            break;
        case 'N':
            retList.at(8) = 1;
            break;
        default:
            std::cerr << "Error: race " << pt.getAge() << "not indentified.";
            exit(1);
    }

    if (pt.getCondition() == true)
    {
        retList.at(9) = 1;
    }

    if (pt.getHosp() == true)
    {
        retList.at(10) = 1;
    }

    return retList;
}