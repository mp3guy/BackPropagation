/*
 * Backpropagation.cpp
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 *
 */

#include "Backpropagation.h"

Backpropagation::Backpropagation(const vector<int> & netDescription, int numInputs)
{
	numLayers = netDescription.size();

    srand((unsigned)(time(NULL)));

    layers = new Layer[netDescription.size()];

    for(int i = netDescription.size() - 1; i > -1; i--)
    {
        bool isOutput = i == (int)netDescription.size() - 1;
        bool isInput = i == 0;

        Layer * nextLayer = (isOutput ? 0 : &layers[i + 1]);
        Layer * prevLayer = (isInput ? 0 : &layers[i - 1]);

        layers[i].initialiseLayer(netDescription[i], isOutput, isInput, nextLayer, prevLayer);
    }

    layers[0].connectInput(0, numInputs);

    //No need to connect the input layer yet
    for(int i = 1; i < numLayers; i++)
    {
        layers[i].connectInput(layers[i - 1].getOutput(), layers[i - 1].getNumNeurons());
    }
}

Backpropagation::~Backpropagation()
{
    delete [] layers;
}

double Backpropagation::train(Pattern & inPattern)
{
    assert(inPattern.getNumInputs() == layers[0].getNumInputs());

    lastPattern = &inPattern;

    layers[0].setInput(inPattern.getInputs());

    feedForward();

    backPropagate();

    updateWeights();

    calculateError();
    return lastError;
}

void Backpropagation::feedForward(double * input)
{
    if(input != 0)
    {
        layers[0].setInput(input);
    }

    layers[0].feedForward();
}

double * Backpropagation::getOutput()
{
    return layers[numLayers - 1].getOutput();
}

void Backpropagation::backPropagate()
{
    for(int i = 0; i < layers[numLayers - 1].getNumNeurons(); i++)
    {
        layers[numLayers - 1].getNeurons()[i].setError((lastPattern->getOutput()[i] - layers[numLayers - 1].getOutput()[i]) * Sigmoid::sigFuncPrime(layers[numLayers - 1].getOutput()[i]));
    }
    layers[numLayers - 2].backPropagate();
}

void Backpropagation::updateWeights()
{
    layers[0].updateWeights();
}

void Backpropagation::calculateError()
{
    lastError = 0.0;

    for(int i = 0; i < layers[numLayers - 1].getNumNeurons(); i++)
    {
        lastError += 0.5 * pow(lastPattern->getOutput()[i] - layers[numLayers - 1].getOutput()[i], 2);
    }
}
