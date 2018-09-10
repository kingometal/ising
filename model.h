#ifndef MODEL_H
#define MODEL_H

#include "modelinterface.h"
//int *s, *sm;//das Gitter und zusaetzliche Arrays zur Mittelwertbildung
//int m;//Magnetisierung


class Model: public ModelInterface
{
public:
    Model();
    Model(int width, int height);
    ~Model();

    int GridWidth;
    int GridHeight;
    int *NodeMagnetization;
    int *MeanNodeMagnetization;
    int TotalMagnetization;
    double T;
    double dT;
    double H;
    double dH;
    double J;
    double ETh; //Thermal energy

    void SetGridWidth(int width);
    void SetGridHeight(int height);
    void InitModel();
    void SetLattice();
    void SetGrid(int width, int height);

    int GetWidth();
    int GetHeight();
    bool GetBinaryData(int x, int y);
    int GetData(int x, int y);

    void Iterate();
    void KeyPressed(char key);
private:
    int flip(int x, int y);
    int GetMagnetization(int x, int y);
    int SetNodeMagnetization(int x, int y, int value);
    void updateT();
};

#endif //MODEL_H
