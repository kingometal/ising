#include "model.h"
#include <stdlib.h>
#include <iostream>

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

Model::Model()
{

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

void Model::SetGridWidth(int width)
{
    SetGrid(GridHeight,width);
}

void Model::SetGridHeight(int height)
{
    SetGrid(height, GridWidth);
}

int Model::InitModel()
{
    T = 1940.0;
//    updateT();
    dT = 1.000;
    H = 0.001;// in eV
    dH = 0.001;
    J = 0.042;// in eV
//    update_strings();
   return SetLattice();
}

// das eigentliche gitter und die gitter zur mittelwertbildung werden gefuellt
// das eigentliche gitter ist nach zufall mit -1 oder 1 gefuellt;
// die anfangs-magnetisierung und die anfangsenergie werden auch gleich berechnet
int Model::SetLattice(){
    TotalMagnetization = 0;
    if (GridWidth <= 0 || GridHeight <= 0) return 0;
    for (int i = 0; i < GridWidth; i++){
        for (int j = 0; j < GridHeight; j++)
        {
            int index = i*GridHeight + j;
            NodeMagnetization[index] = 2*(rand()%2) - 1;
            MeanNodeMagnetization[index] = 0;
            TotalMagnetization += NodeMagnetization[index];
        }
    }
    //Ecurrent = Ef();
    return 1;
}
