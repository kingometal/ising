#include "model.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

namespace
{
const double BOLTZMANN_CONST = 0.00008673324; //Boltzmann constant;
const double DEFAULT_TEMPERATURE = 1940.0; // in K (Kelvin)
const double DEFAULT_TEMPERATURE_STEP = 1.000; // in K
const double DEFAULT_MAGNETIC_FIELD = 0.001; // in eV (electronvolt)
const double DEFAULT_MAGNETIC_FIELD_STEP = 0.001; // in eV
const double DEFAULT_J = 0.042; // interaction energy in eV
const double MINIMUM_MAGNETIC_FIELD_STEP = 0.0000000001;
const double MINIMUM_TEMPERATURE_STEP = 0.0000000001;
}

using namespace Ising;

Model::Model(int width, int height)
    : GridWidth(width)
    , GridHeight(height)
    , NodeMagnetization(NULL)
    , MeanNodeMagnetization(NULL)
    , TotalMagnetization(0)
    , ChecksPerIteration(width*height)
    , T(DEFAULT_TEMPERATURE)
    , dT(DEFAULT_TEMPERATURE_STEP)
    , H(DEFAULT_MAGNETIC_FIELD)
    , dH(DEFAULT_MAGNETIC_FIELD_STEP)
    , J (DEFAULT_J)
    , ETh(exp ((long double) -2.0/(T * BOLTZMANN_CONST)))
{
    ReinitGrid(width, height);
    ReinitModel();
}

Model::~Model()
{
    DeinitGrid();
}

void Model::DeinitGrid()
{
    if (NULL != NodeMagnetization)
    {
        delete NodeMagnetization;
        NodeMagnetization = NULL;
    }
    if (NULL != MeanNodeMagnetization)
    {
        delete MeanNodeMagnetization;
        MeanNodeMagnetization = NULL;
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
        NodeMagnetization = (int*) malloc((int)sizeof(int)*NN); //das eigentliche gitter
        MeanNodeMagnetization = (int*) malloc((int)sizeof(int)*NN); // zur mittelwertbildung
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
    return (GetNodeMagnetization(x,y) > 0);
}

int Model::GetData(int x, int y)
{
    return 0;
}

int Model::GetNodeMagnetization(int x, int y)
{
    return NodeMagnetization[x*GridHeight + y];
}

int Model::GetNodeMagnetization(int index)
{
    return NodeMagnetization[index];
}

int Model::SetNodeMagnetization(int x, int y, int value)
{
    NodeMagnetization[x*GridHeight + y] = value;
}

void Model::Iterate()
{
    int w = GridWidth;
    int h = GridHeight;
    int mf = 0; // Mean field, in this case the sum of the neighbour spins magnetizations
    int x = 0;
    int y = 0;
    int xh = 0; // variable to save computation effort
    int index = 0; // Node position in a 1D array
    int indexUpper = 0;
    int indexLower = 0;
    int indexRight = 0;
    int indexLeft = 0;
    for (int i = 0; i < ChecksPerIteration; i++)
    {
        mf = 0;
        x = rand()%w;//zufaellig ausgewaehlter spin
        y = rand()%h;//zufaellig ausgewaehlter spin
        xh = x*h;
        index = xh + y;
        indexUpper = xh + (y+h-1)%h;
        indexLower= xh + (y+1)%h;
        indexLeft = ((x+w-1)%w)*h + y;
        indexRight = ((x+1)%w)*h + y;

        mf = GetNodeMagnetization(indexUpper) + GetNodeMagnetization(indexLower) + GetNodeMagnetization(indexLeft) + GetNodeMagnetization(indexRight);

        double dE = (J*mf + H)*GetNodeMagnetization(index); // energy difference. The 2 is taken into account within ETh

        if ( dE <= 0 || pow(ETh, dE)*RAND_MAX > rand()) {
            FlipNodeSpin(x,y);
        }
    }
}

void Model::KeyPressed(KeyCode key)
{
    switch(key)
    {
    case KEY_NUM_PLUS:      T += dT; ETh = exp ((long double) -2.0/(T * BOLTZMANN_CONST)); printf ("Temperature is now %f\n", T); break;
    case KEY_NUM_MINUS:     T = (T>dT)?T-dT:0.0; ETh = exp ((long double) -2.0/(T * BOLTZMANN_CONST)); printf ("Temperature is now %f\n", T); break;
    case KEY_NUM_MULTIPLY:  H += dH; printf ("Magnetic Field is now %f\n", H); break;
    case KEY_NUM_DIVIDE:    H -= dH; printf ("Magnetic Field is now %f\n", H); break;
    case KEY_ARROW_LEFT:    dH = (dH <= MINIMUM_MAGNETIC_FIELD_STEP)?MINIMUM_MAGNETIC_FIELD_STEP:dH/10; printf ("Magnetic Field Spep is now %f\n", dH); break;
    case KEY_ARROW_RIGHT:   dH = dH * 10; printf ("Magnetic Field Spep is now %f\n", dH); break;
    case KEY_ARROW_DOWN:    dT = (dT <= MINIMUM_TEMPERATURE_STEP)?MINIMUM_TEMPERATURE_STEP:dT/10 ; printf ("Temperature Step is now %f\n", dT); break;
    case KEY_ARROW_UP:      dT = dT * 10; printf ("Temperature Step is now %f\n", dT); break;
    case KEY_A:             ChecksPerIteration = (ChecksPerIteration<=1)?1:ChecksPerIteration/2; printf ("Speed is now %i\n", ChecksPerIteration); break;
    case KEY_S:             ChecksPerIteration *= 2; printf ("Speed is now %i\n", ChecksPerIteration); break;
    default: break;
    }
}

int Model::FlipNodeSpin(int x, int y){
    SetNodeMagnetization(x, y, -GetNodeMagnetization(x,y));
    TotalMagnetization += 2*GetNodeMagnetization(x,y);
}


void Model::SetGridWidth(int width)
{
    ReinitGrid(GridHeight,width);
}

void Model::SetGridHeight(int height)
{
    ReinitGrid(height, GridWidth);
}

void Model::ReinitModel()
{
    T = DEFAULT_TEMPERATURE;

    dT = DEFAULT_TEMPERATURE_STEP;
    H = DEFAULT_MAGNETIC_FIELD;// in eV
    dH = DEFAULT_MAGNETIC_FIELD_STEP;
    J = DEFAULT_J;// in eV

    ETh = exp ((long double) -2.0/(T*BOLTZMANN_CONST));
    ResetMagnetizationState();
}

void Model::ResetMagnetizationState(){
    TotalMagnetization = 0;
    for (int x = 0; x < GridWidth; x++){
        for (int y = 0; y < GridHeight; y++)
        {
            SetNodeMagnetization(x,y, 2*(rand()%2) - 1);
            TotalMagnetization += GetNodeMagnetization(x,y);
        }
    }
}
