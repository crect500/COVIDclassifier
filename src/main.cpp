#include <vector>
#include <iostream>
#include <cmath>

#include "../lib/Patient.h"
#include "../lib/Binary_classifier.h"
#include "../lib/util.h"

int main()  {
    std::vector<Patient> pt;
    std::array<std::vector<std::array<double, 11>>, 2> data;
    std::vector<std::array<double, 11>> training_set, test_set;

    Binary_classifier model(pow(10, -2));
    pt = load_patients("../data/medData.csv");
    data = split(pt, 0.8);
    training_set = data.at(0);
    test_set = data.at(1);
    model.train(training_set, 100);
    model.test(test_set);
    
    return 0;
}