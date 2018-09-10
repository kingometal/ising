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
    , SourceDistance(100)
    , TimeStage(0.0)
    , TimeStep(0.1)
    , K(0.1)
    , Omega(5)
    , Nodes()
    , Amplitude()
{
    ReinitGrid(width, height);
}

Model::~Model()
{
    DeinitGrid();
}

void Model::DeinitGrid()
{
    Amplitude.clear();
    Nodes.clear();
}

void Model::ReinitGrid(int width, int height)
{
    GridHeight = height;
    GridWidth = width;
    int NN = width * height;
    DeinitGrid();
    if (NN > 0)
    {
        for (int i = 0; i < NN; i++)
        {
            Amplitude.push_back(0.5);
        }

        Source Sources[SourceCount];
        for (int q = 0; q < SourceCount; q++)
        {
            Sources[q].x = width/2+(((q%2)*2)-1)*(q/2 + 1)*SourceDistance/2;
            std::cout << Sources[q].x << std::endl;
            Sources[q].y = 0.0;
        }

        try
        {
        for (int x = 0; x < GridWidth; x++)
        {
            for (int y = 0; y < GridHeight; y++)
            {
                int i = x*GridHeight + y;
                Node n;
                for (int q = 0; q < SourceCount; q++)
                {
                    n.distanceToSource.push_back(sqrt(pow(Sources[q].x - x, 2) + pow(Sources[q].y - y, 2)));
                }
                Nodes.push_back(n);
            }
        }
        }
        catch (...)
        {
            std::cout << "exception" << std::endl;
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
    double TimeComponent = Omega*TimeStage;
    for (int x = 0; x < GridWidth; x++)
    {
        int indexx = x*GridHeight;
        for (int y = 0; y < GridHeight; y++)
        {
            int i = indexx + y;
            Amplitude[i] = 0.0;
            for (int q = 0; q < SourceCount; q++)
            {
                Amplitude[i] += sin(K*Nodes[i].distanceToSource[q] - TimeComponent);
            }
            Amplitude[i] *= (MAX_AMPLITUDE/SourceCount);

        }
    }
}

void Model::KeyPressed(KeyCode key)
{
    switch(key)
    {
    case KEY_NUM_PLUS: SourceDistance+=10; ReinitGrid(GridWidth,GridHeight);  break;
    case KEY_NUM_MINUS: SourceDistance -=10; ReinitGrid(GridWidth,GridHeight);    break;
    case KEY_NUM_MULTIPLY:  Omega+= 1; break;
    case KEY_NUM_DIVIDE: Omega-=1;   break;
    case KEY_ARROW_LEFT: K -= 0.05;   break;
    case KEY_ARROW_RIGHT:K += 0.05;   break;
    case KEY_ARROW_DOWN: SourceCount--; ReinitGrid(GridWidth,GridHeight);    break;
    case KEY_ARROW_UP: SourceCount++; ReinitGrid(GridWidth,GridHeight);     break;
    case KEY_A:             break;
    case KEY_S:             break;
    default: break;
    }
}
