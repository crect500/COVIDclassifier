#ifndef BINARY_CLASSIFIER_HEADER
#define BINARY_CLASSIFIER_HEADER

#include <vector>
#include <array>

#include "../lib/Patient.h"

class Binary_classifier{
    /** 
     * @brief Binary classifier based on logistic regression
     *
     * This class provides the environment for a logistic regression architecture to train and 
     * test itself. It is built for the CDC COVID patient data set, and accepts samples with
     * 10 variables and one target element. The weights are stored in the @p param array, for which
     * the elements correspond to the following acceptable inputs:
     *      0 - Age (>0) [exp(r * Age)]
     *      1 - Male (1 or 0)
     *      2 - Female (1 or 0)
     *      3 - Hawaiian/Pacific Islander (1 or 0)
     *      4 - White (1 or 0)
     *      5 - Black (1 or 0)
     *      6 - Asian (1 or 0)
     *      7 - Hispanic/Latino (1 or 0)
     *      8 - Native American/Alaska Native (1 or 0)
     *      9 - Underlying Medical Condition (1 or 0)
     */
    public:
        /**
		 * @brief Default constructor for the Binary_classifier class
		 *
		 * This default constructor initializes the Binary_classifier class with no parameters. It sets
		 * @p params acoording to the default values specified in the Binary_classifier::init() function
         * implementation. It sets the @p learn_rate to 0.1.
		 */
        Binary_classifier();

        /**
		 * @brief One parameter constructor for the Binary_classifier class with learning rate specified.
		 *
		 * This constructor initializes the Binary_classifier class with the specified learning rate. It sets
		 * @p params acoording to the default values specified in the Binary_classifier::init() function
         * implementation.
		 */
        Binary_classifier(double alpha);

        /**
		 * @brief Default training wrapper function for the classifier.
		 *
		 * Uses a stochastic gradient descent algorithm to iteratively train the model to an acceptable
         * value of the loss function. The stop value for the loss function can be specified in the
         * implementation. Updates the @p param values as it progresses.
		 *
		 * @p data Vector of sample points representing the dataset.
		 */
        void train(std::vector<std::array<double, 11>> const data);

        /**
		 * @brief Training wrapper function for the classifier with maximum iterations specified.
		 *
		 * Uses a stochastic gradient descent algorithm to iteratively train the model to an acceptable
         * value of the loss function. The stop value for the loss function can be specified in the
         * implementation. Updates the @p param values as it progresses.
		 *
		 * @p data Vector of sample points representing the dataset.
         * @p max_iter Unsigned integer which specifies the number of iterations of gradient descent.
		 */
        void train(std::vector<std::array<double, 11>> const data, unsigned int max_iter);

        /**
		 * @brief Testing wrapper function for the classifier.
		 *
		 * Calculates the ideal threshold value for the model and the associated True Postive Rate (TPR) and
         * False Positive Rate (FPR). Displays this information to the standard output.
		 *
		 * @p data Vector of sample points representing the dataset.
		 */
        void test(std::vector<std::array<double, 11>> const data);

        std::array<double, 10> getModel() const {return param;};
    private:
        /**
		 * @brief Initializes the model weights.
		 *
		 * Initial guesses of model weights are specified in this function implementation.
		 */
        void init();

        double learn_rate;
        std::array<double, 10> param;
};
#endif