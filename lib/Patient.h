#ifndef PATIENT_HEADER
#define PATIENT_HEADER

#include <string>

class Patient   {
    public:
        /**
		 * @brief Default constructor for the Patient class.
		 *
		 * This default constructor initializes the Patient class with the data provided.
         * 
         * @p age Unsigned integer representing patient age.
         * @p male Boolean value representing the sex of the patient. True (1) for male and False (0) for female.
         * @p condition Boolean value signifying an underlying medical condition. True (1) for yes and False (0) for no.
         * @p hosp Boolean value signifying whether the patient was hospitalized. True (1) for yes and False (0) for no.
         * @p race Char which encodes race as a binary value.
         *          I - Hawaiian/Pacific Islander
         *          W - White
         *          B - Black
         *          A - Asian
         *          H - Hispanic/Latino
         *          N - Native American/Alaska Native
		 */
        Patient(short unsigned int pt_age, bool pt_male, bool pt_condition, bool pt_hosp, char pt_race);

        short unsigned int getAge()     {return age;};
        bool getMale()   {return male;};
        bool getCondition()    {return condition;};
        bool getHosp()      {return hosp;};
        char getRace()      {return race;};
    
    private:
        short unsigned int age;
        char race;
        bool male;
        bool condition;
        bool hosp;
};

#endif