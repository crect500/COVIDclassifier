#include "../lib/Binary_classifier.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <cmath>

/**
 * @brief Computes the dot product of the weight vector and the input.
 *
 * Performs element-wise multiplication across the two arrays.
 *
 * @p x Array of input values.
 * @p w Array of weight values.
 * 
 * @return Double representing the value of the dot product.
 */
double xw(std::array<double, 11> const x, std::array<double, 10> const w);

/**
 * @brief Computes the sigmoid value of the dot product of the weight and input array.
 *
 * Implements both a sigmoid and stable sigmoid caculation based on the returned value
 * of the dot product.
 *
 * @p x Array of input values.
 * @p w Array of weight values.
 * 
 * @return Double representing the value of the sigmoid function.
 */
double sigmoid(std::array<double, 11> const x, std::array<double, 10> const w);

/**
 * @brief Computes the maximum likelihood loss for the current data.
 *
 * Calculates the maximum likelihood loss for the current data using a sigmoid activation
 * function.
 *
 * @p data Vector of sample points representing the dataset.
 * @p w Array of weight values.
 * 
 * @return Double representing the value of the loss function.
 */
double loss(std::vector<std::array<double, 11>> const data, std::array<double, 10> const w);

/**
 * @brief Updates the model based of a gradient descent method.
 *
 * Wrapper function for an iterative stochastic gradient descent
 * algorithm which decreases the value of the loss function based
 * on data. Updates the weight values in place.
 *
 * @p data Vector of sample points representing the dataset.
 * @p w Vector of weight values.
 * @p alpha Learning rate for the trainer.
 */
void update_w(std::vector<std::array<double, 11>> const data, std::array<double, 10>& w, double alpha);

/**
 * @brief Stochastic gradient descent method
 *
 * Implements one iteration of gradient descent over the entire
 * provided dataset. Returns the gradient for each weight value.
 *
 * @p data Vector of sample points representing the dataset.
 * @p w Array of weight values.
 * 
 * @return Array of gradient values.
 */
std::array<double, 10> grad_descent(std::vector<std::array<double, 11>> const data, std::array<double, 10> const w);

Binary_classifier::Binary_classifier()     {
    learn_rate = 0.1;
    init();
}

Binary_classifier::Binary_classifier(double alpha)       {
    learn_rate = alpha;
    init();
}

void Binary_classifier::train(std::vector<std::array<double, 11>> const data)    {
    unsigned int max_iter = 100;
    unsigned int count = 0;
    double L = loss(data, param);
    double L_old = L + 100000;

    std::cout << L << std::endl;
    while (L > 1000 && count < max_iter && ((L_old - L) / L_old) > 0.00001)
    {
        L_old = L;
        update_w(data, param, learn_rate);
        L = loss(data, param);
        std::cout << L << std::endl;
    }
}

void Binary_classifier::train(std::vector<std::array<double, 11>> const data, unsigned int max_iter) {
    unsigned int count = 0;
    double L = loss(data, param);
    double L_old = L + 100000;
    unsigned int index = rand() % data.size();

    std::cout << L << std::endl;
    while (L > 1000 && count < max_iter && ((L_old - L) / L_old) > 0.00001)
    {
        L_old = L;
        update_w(data, param, learn_rate);
        L = loss(data, param);

        #ifdef DEBUG
        std::cout << "w: ";
        for (auto i = param.begin(); i != param.end(); i++)
        {
            std::cout << std::setprecision(4) << std::fixed << *i << ' ';
        }
        std::cout << std::endl << "Loss: " << L << "\n\n";
        #endif
    }

}

void Binary_classifier::test(std::vector<std::array<double, 11>> const data)   {
    unsigned int TP = 0;
    unsigned int FP = 0;
    unsigned int TN = 0;
    unsigned int FN = 0;
    unsigned int res = 100;
    unsigned int count = 1;
    double h = 0;
    double thresh = 0;
    double ideal = 0;
    double eval = 0;
    double ideal_TPR = 0;
    double ideal_FPR = 0;
    double ideal_thresh = 0;
    
    for (unsigned int i = 0; i < res; i++)
    {
        TP = 0;
        FP = 0;
        TN = 0;
        FN = 0;
        thresh = float(i)/float(res);

        for (auto j = data.begin(); j != data.end(); j++)
        {
            h = sigmoid(*j, param);
            if (h > thresh && (j -> at(10) == 1))
            {
                TP++;
            }
            else if (h > thresh && (j -> at(10) == 0))
            {
                FP++;
            }
            else if (h <= thresh && (j -> at(10) == 0))
            {
                TN++;
            }
            else
            {
                FN++;
            }
        }

        eval = float(TP) / (TP + FN) - float(FP) / (FP + TN);

        #ifdef DEBUG
        std::cout << TP << '\t' << FP << '\t' << TN << '\t' << FN << '\t' << eval << '\n';
        #endif

        if (eval > ideal)
        {
            ideal = eval;
            ideal_thresh = thresh;
            ideal_TPR = float(TP) / (TP + FN);
            ideal_FPR = float(FP) / (FP + TN);
        }
    }
    
    std::cout << "The model achieved a TPR of " << ideal_TPR * 100 << "% and FPR of " << ideal_FPR * 100 << "% at a threshold of " << ideal_thresh;
}

void Binary_classifier::init()   {
    param.at(0) = 0.3028;
    param.at(1) = -2.1861;
    param.at(2) = -2.5518;
    param.at(3) = -0.4612;
    param.at(4) = -2.5132;
    param.at(5) = -1.4031;
    param.at(6) = -1.5652;
    param.at(7) = -1.5934;
    param.at(8) = 0.5180;
    param.at(9) = 1.3101;    
}

double xw(std::array<double, 11> const x, std::array<double, 10> const w)
{
    double sum = 0;
    unsigned int n = w.size();
    for (short unsigned int i = 0; i < n; i++)
    {
        sum += x.at(i) * w.at(i);
    }

    return sum;
}

double sigmoid(std::array<double, 11> const x, std::array<double, 10> const w)    {
    double retVal = 0;
    double z = xw(x, w);
    double f = 0;

    if (z >= 0)
    {
        f = exp(-z);
        retVal = 1 / (1 + f); 
    }
    else
    {
        f = exp(z);
        retVal = f / (1 + f);
    }

    return retVal;
}

double loss(std::vector<std::array<double, 11>> const data, std::array<double, 10> const w) {
    double z = 0;
    double L = 0;
    int count = 1;

    for (auto i = data.begin(); i != data.end(); i++)   
    {
        z = xw(*i, w);
        L += log(1 + exp(z)) - (i -> at(10) * z);
    }

    return L;
}

void update_w(std::vector<std::array<double, 11>> const data, std::array<double, 10>& w, double alpha)
{
    unsigned int n = data.size();
    std::array<double, 10> dw;

    dw = grad_descent(data, w);
    for (auto i = dw.begin(); i != dw.end(); i++)
    {
        *i /= n;
    }

    #ifdef DEBUG
        std::cout << "dw: ";
        for (auto i = dw.begin(); i != dw.end(); i++)
        {
            std::cout << std::setprecision(4) << *i << ' ';
        }
        std::cout << std::endl;
    #endif

    for (unsigned int i = 0; i < 10; i++)
    {
        w.at(i) -= dw.at(i) * alpha;
    }
}

std::array<double, 10> grad_descent(std::vector<std::array<double, 11>> const data, std::array<double, 10> const w)
{
    std::array<double, 10> dw;
    double sig = 0;
    double f = 0;

    for (auto i = dw.begin(); i != dw.end(); i++)
    {
        *i = 0;
    }

    for (auto i = data.begin(); i != data.end(); i++)
    {
        sig = sigmoid(*i, w);
        f = sig - (i -> at(10));
        for (unsigned int j = 0; j < 10; j++)
        {
            dw.at(j) += f * i -> at(j);
        }
    }

    return dw;
}