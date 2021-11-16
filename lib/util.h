#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

#include "Patient.h"

std::vector<Patient> load_patients(std::string filename);
std::array<std::vector<std::array<double, 11>>, 2> split(std::vector<Patient> data, double frac);
#endif