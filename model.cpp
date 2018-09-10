#include "model.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

//die Gitterseitenlaenge N wird festgelegt, und alles, was davon abhaengt wird erneuert
//int setN(int argv){
//    if (argv > 0){
//        N = argv;
//        NN = N*N;
//        N2 = 2*N;
//        speed = 1.0*NN;
//        rezNN = 1.0/(double)NN;
//        s = (int*) malloc((int)sizeof(int)*NN); //das eigentliche gitter
//        sm = (int*) malloc((int)sizeof(int)*NN); // zur mittelwertbildung
//        SizeN = Size*N; // falls das fenster skaliert sein soll
//        height = SizeN+90; //90 px reservieren wir fuer die textausgabe
//        width = (SizeN<300)?300:SizeN; // mindestens 300 px fuer die textausgabe
//        return 1;
//    }
//    else return 0;
//}

namespace
{
const double BOLTZMANN_CONST = 0.00008673324; //Boltzmann-Konstante;
}

Model::Model()
{

}

Model::Model(int width, int height)
{
    GridWidth = width;
    GridHeight = height;
    SetGrid(width, height);
    InitModel();
}

Model::~Model()
{

}


void Model::SetGrid(int width, int height)
{
    GridHeight = height;
    GridWidth = width;
    int NN = width * height;
    if (NN > 0)
    {
        NodeMagnetization = (int*) malloc((int)sizeof(int)*NN); //das eigentliche gitter
        MeanNodeMagnetization = (int*) malloc((int)sizeof(int)*NN); // zur mittelwertbildung
    }
    else
    {
        std::cout << "can not set grid yet: width or height is zero : " << width << " : " << height << std::endl;
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
    return (GetMagnetization(x,y) > 0);
}

int Model::GetData(int x, int y)
{
    return 0;
}

int Model::GetMagnetization(int x, int y)
{
    return NodeMagnetization[x*GridHeight + y];
}

int Model::SetNodeMagnetization(int x, int y, int value)
{
    NodeMagnetization[x*GridHeight + y] = value;
}

void Model::Iterate()
{
    int w = GridWidth;
    int h = GridHeight;

    for (int i = 0; i < w*h/10; i++)
    {
        int mf = 0;

        int x = rand()%w;//zufaellig ausgewaehlter spin
        int y = rand()%h;//zufaellig ausgewaehlter spin

        if (x > 0 && x < w-1 && y > 0 && y < w-1){// wenn der spin i im inneren ist, brauche ich kein modulo fuer die nachbarindices
            mf = GetMagnetization(x,y-1) + GetMagnetization(x,y+1) + GetMagnetization(x+1,y) + GetMagnetization(x-1,y) ;
        }
        else
        {
            mf = GetMagnetization(x,(y+h-1)%h) + GetMagnetization(x,(y+1)%h) + GetMagnetization((x+1)%w,y) + GetMagnetization((x+w-1)%w,y) ;
        }

        double dE = (J*mf + H)*GetMagnetization(x,y); // die Energiedifferenz. die 2 ist in eT versteckt

        if ( dE <= 0 || pow(ETh, dE)*RAND_MAX > rand()) {
            flip(x,y);
        }
    }
}

void Model::KeyPressed(char key)
{

}

int Model::flip(int x, int y){
    SetNodeMagnetization(x, y, -GetMagnetization(x,y));
    TotalMagnetization += 2*GetMagnetization(x,y);
}


void Model::SetGridWidth(int width)
{
    SetGrid(GridHeight,width);
}

void Model::SetGridHeight(int height)
{
    SetGrid(height, GridWidth);
}

void Model::InitModel()
{
    T = 1940.0;
    updateT();
    dT = 1.000;
    H = 0.001;// in eV
    dH = 0.001;
    J = 0.042;// in eV
    SetLattice();
}

void Model::updateT (){
    double kBT = T*BOLTZMANN_CONST;
    ETh = exp ((long double) -2.0/(kBT));
}

void Model::SetLattice(){
    TotalMagnetization = 0;
    for (int x = 0; x < GridWidth; x++){
        for (int y = 0; y < GridHeight; y++)
        {
            SetNodeMagnetization(x,y, 2*(rand()%2) - 1);
            TotalMagnetization += GetMagnetization(x,y);
        }
    }
}
