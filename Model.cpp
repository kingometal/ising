#include "Model.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

namespace
{
    const double MAX_AMPLITUDE = 1.0;
}

using namespace Waves;

Model::Model(int width, int height)
    : GridWidth(width)
    , GridHeight(height)
    , SourceCount(2)
    , TimeStage(0.0)
    , TimeStep(0.1)
    , Nodes(NULL)
    , Amplitude(NULL)
{
    ReinitGrid(width, height);
}

Model::~Model()
{
    DeinitGrid();
}

void Model::DeinitGrid()
{
    if (NULL != Amplitude)
    {
        delete Amplitude;
        Amplitude = NULL;
    }
    if (NULL != Nodes)
    {
        delete Nodes;
    }
}

void Model::ReinitGrid(int width, int height)
{
    GridHeight = height;
    GridWidth = width;
    int NN = width * height;

    DeinitGrid();

    if (NN > 0)
    {
        Amplitude = (double*) malloc((int)sizeof(double)*NN); // the grid
        for (int i = 0; i < NN; i++)
        {
            Amplitude[i]=0.5;
        }
        Source Sources[SourceCount];
        Sources[0].x = 100.0;
        Sources[0].y = 0.0;
        Sources[1].x = 110.0;
        Sources[1].y = 0.0;

        Nodes = (Node*) malloc((int)sizeof(Node)*NN); // the grid
        for (int x = 0; x < GridWidth; x++)
        {
            for (int y = 0; y < GridHeight; y++)
            {
                int i = x*GridHeight + y;
                for (int q = 0; q < SourceCount; q++)
                {
                    Nodes[i].distanceToSource.push_back(sqrt(pow(Sources[q].x - x, 2) + pow(Sources[q].y - y, 2)));
                }
            }
        }
    }
    else
    {
        std::cerr << "can not set grid yet: width or height is zero : " << width << " : " << height << std::endl;
    }
}

int Model::GetWidth()
{
    return GridWidth;
}

int Model::GetHeight()
{
    return GridHeight;
}

bool Model::GetBinaryData(int x, int y)
{
    return 0;
}

double Model::GetNormalizedData(int x, int y)
{
    double amp = Amplitude[x*GridHeight + y];
    return amp>MAX_AMPLITUDE?1.0:amp<-MAX_AMPLITUDE?0.0:((amp/(2*MAX_AMPLITUDE))+1)/2.0;
}

double Model::GetAmplitude(int x, int y)
{
    return Amplitude[x*GridHeight + y];
}

int Model::SetAmplitude(int x, int y, double value)
{
    Amplitude[x*GridHeight + y] = value;
}

void Model::Iterate()
{
    TimeStage += TimeStep;
    double omega = 5.0;
    double TimeComponent = omega*TimeStage;
    for (int x = 0; x < GridWidth; x++)
    {
        int indexx = x*GridHeight;
        for (int y = 0; y < GridHeight; y++)
        {
            int i = indexx + y;
            Amplitude[i] = 0.0;
            for (int q = 0; q < SourceCount; q++)
            {
                Amplitude[i] += sin(Nodes[i].distanceToSource[q] - TimeComponent);
            }
            Amplitude[i] *= (MAX_AMPLITUDE/SourceCount);

        }
    }
}

void Model::KeyPressed(KeyCode key)
{
    switch(key)
    {
    case KEY_NUM_PLUS:      break;
    case KEY_NUM_MINUS:     break;
    case KEY_NUM_MULTIPLY:  break;
    case KEY_NUM_DIVIDE:    break;
    case KEY_ARROW_LEFT:    break;
    case KEY_ARROW_RIGHT:   break;
    case KEY_ARROW_DOWN:    break;
    case KEY_ARROW_UP:      break;
    case KEY_A:             break;
    case KEY_S:             break;
    default: break;
    }
}
