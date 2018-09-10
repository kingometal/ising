#ifndef MODEL_H
#define MODEL_H

#include "ModelInterface.h"

namespace Ising
{
class Model: public ModelInterface
{
public:
    Model(int width, int height);
    ~Model();

    int GridWidth;
    int GridHeight;
    int *NodeMagnetization;
    int *MeanNodeMagnetization;
    int TotalMagnetization;
    int ChecksPerIteration; // How many nodes are calculated in one iteration
    double T;
    double dT;
    double H;
    double dH;
    double J;
    double ETh; //Thermal energy

    void SetGridWidth(int width);
    void SetGridHeight(int height);
    void ReinitModel();
    void ResetMagnetizationState();


    int GetWidth();
    int GetHeight();
    bool GetBinaryData(int x, int y);
    int GetData(int x, int y);

    void Iterate();
    void KeyPressed(KeyCode key);
private:
    int FlipNodeSpin(int x, int y);
    int GetNodeMagnetization(int x, int y);
    int SetNodeMagnetization(int x, int y, int value);
    void ReinitGrid(int width, int height);
    void DeinitGrid();
    int GetNodeMagnetization(int index);
};
} // namespace
#endif //MODEL_H
