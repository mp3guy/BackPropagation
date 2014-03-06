/*
 * Neuron.cpp
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 */

#include "Neuron.h"

Neuron::Neuron()
{
}

Neuron::~Neuron()
{
    delete [] weights;
    delete [] prevWeightDelta;
}

void Neuron::initialiseNeuron(double * inInput, int inNumInputs)
{
    input = inInput;
    numInputs = inNumInputs;
    weights = new double[inNumInputs + 1];
    prevWeightDelta = new double[inNumInputs + 1];

    for(int i = 0; i < numInputs + 1; i++)
    {
        weights[i] = (double) (rand()) / (RAND_MAX / 2) - 1;
        prevWeightDelta[i] = 0.0;
    }
}

void Neuron::setInput(double * inInput)
{
    input = inInput;
}

double Neuron::getOutput()
{
    return output;
}

double * Neuron::getInput()
{
    return input;
}

void Neuron::setError(double inError)
{
    error = inError;
}

double Neuron::getError()
{
    return error;
}

double * Neuron::getWeights()
{
    return weights;
}

double * Neuron::getPrevWeightDelta()
{
    return prevWeightDelta;
}

int Neuron::getNumInputs()
{
    return numInputs;
}

double Neuron::fire()
{
    output = Sigmoid::sigFunc(getWeightedSum());
    return output;
}

double Neuron::getWeightedSum()
{
    double sum = 0.0;

    for(int i = 0; i < numInputs; i++)
    {
        sum += weights[i] * input[i];
    }

    sum += weights[numInputs];

    return sum;
}
