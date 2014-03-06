/*
 * Pattern.h
 *
 *  Created on: 26 Dec 2010
 *      Author: thomas
 */

#ifndef PATTERN_H_
#define PATTERN_H_

class Pattern
{
    public:
        Pattern(int numInputs, double * inputs, double * expectedOutput);
        virtual ~Pattern();

        double * getInputs();
        int getNumInputs();
        double * getOutput();

    private:
        int numInputs;
        double * inputs;
        double * expectedOutput;
};

#endif /* PATTERN_H_ */
