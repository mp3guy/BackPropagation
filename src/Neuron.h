/*
 * Neuron.h
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <stdlib.h>
#include "Sigmoid.h"

class Neuron
{
    public:
        Neuron();
        virtual ~Neuron();

        void initialiseNeuron(double * inInput, int inNumInputs);
        void setInput(double * inInput);
        double getOutput();

        double fire();
        double getWeightedSum();

        void setError(double inError);
        double getError();

        double * getWeights();
        double * getPrevWeightDelta();
        int getNumInputs();
        double * getInput();

    private:
        double * input;
        double * weights;
        double * prevWeightDelta;
        double output;
        double error;
        int numInputs;
};

#endif /* NEURON_H_ */
