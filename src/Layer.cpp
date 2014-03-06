/*
 * Layer.cpp
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 */

#include "Layer.h"

Layer::Layer()
{

}

Layer::~Layer()
{
    delete [] neurons;
    delete [] output;
}

void Layer::initialiseLayer(int inNumNeurons, bool inOutput, bool inInput, Layer * inNextLayer, Layer * inPrevLayer)
{
    isOutput = inOutput;
    isInput = inInput;

    numNeurons = inNumNeurons;
    neurons = new Neuron[numNeurons];
    output = new double[numNeurons];

    nextLayer = inNextLayer;
    prevLayer = inPrevLayer;
}

int Layer::getNumNeurons()
{
    return numNeurons;
}

int Layer::getNumInputs()
{
    return numInputs;
}

Neuron * Layer::getNeurons()
{
    return neurons;
}

double * Layer::getOutput()
{
    return output;
}

void Layer::connectInput(double * inInput, int inNumInputs)
{
    numInputs = inNumInputs;
    input = inInput;

    for(int i = 0; i < numNeurons; i++)
    {
        neurons[i].initialiseNeuron(input, numInputs);
    }
}

void Layer::setInput(double * inInput)
{
    input = inInput;
    for(int i = 0; i < numNeurons; i++)
    {
        neurons[i].setInput(input);
    }
}

void Layer::feedForward()
{
    for(int i = 0; i < numNeurons; i++)
    {
        output[i] = neurons[i].fire();
    }

    if(!isOutput)
    {
        nextLayer->feedForward();
    }
}

void Layer::backPropagate()
{
    for(int i = 0; i < numNeurons; i++)
    {
        double delSum = 0;

        for(int j = 0; j < nextLayer->getNumNeurons(); j++)
        {
            delSum += nextLayer->getNeurons()[j].getError() * nextLayer->getNeurons()[j].getWeights()[i];
        }

        neurons[i].setError(Sigmoid::sigFuncPrime(neurons[i].getOutput()) * delSum);
    }

    if(!isInput)
    {
        prevLayer->backPropagate();
    }
}

void Layer::updateWeights()
{
    for(int i = 0; i < numNeurons; i++)
    {
        for(int j = 0; j < neurons[i].getNumInputs(); j++)
        {
            neurons[i].getWeights()[j] += ALPHA * neurons[i].getPrevWeightDelta()[j];
            neurons[i].getPrevWeightDelta()[j] = LEARNING_RATE * neurons[i].getError() * neurons[i].getInput()[j];
            neurons[i].getWeights()[j] += neurons[i].getPrevWeightDelta()[j];
        }

        neurons[i].getWeights()[neurons[i].getNumInputs()] += ALPHA * neurons[i].getPrevWeightDelta()[neurons[i].getNumInputs()];
        neurons[i].getPrevWeightDelta()[neurons[i].getNumInputs()] = LEARNING_RATE * neurons[i].getError();
        neurons[i].getWeights()[neurons[i].getNumInputs()] += neurons[i].getPrevWeightDelta()[neurons[i].getNumInputs()];
    }

    if(!isOutput)
    {
        nextLayer->updateWeights();
    }
}
