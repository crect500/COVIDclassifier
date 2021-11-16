#include "../lib/Patient.h"

Patient::Patient(short unsigned int pt_age, bool pt_male, bool pt_condition, bool pt_hosp, char pt_race) {
    age = pt_age;
    male = pt_male;
    condition = pt_condition;
    hosp = pt_hosp;
    race = pt_race;
}