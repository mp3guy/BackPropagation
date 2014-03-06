/*
 * Sigmoid.h
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 */

#ifndef SIGMOID_H_
#define SIGMOID_H_

#include <math.h>

class Sigmoid
{
    public:
        static double sigFunc(double value)
        {
            return 1 / (1 + exp(-value));
        }

        static double sigFuncPrime(double value)
        {
            return (1 - value) * value;
        }
};

#endif /* SIGMOID_H_ */
