#ifndef MODEL_H
#define MODEL_H

#include "ModelInterface.h"
#include <vector>

namespace Waves
{

class Source
{
public:
    Source()
        : x (0)
        , y (0)
        , amplitude(0)
    {}
    ~Source() {}
    int x;
    int y;
    double amplitude;
};

class Node
{
    public:
    Node() {}
    ~Node(){}
    std::vector<double> distanceToSource;
};

class Model: public ModelInterface
{
public:
    Model(int width, int height);
    ~Model();

    int GridWidth;
    int GridHeight;
    int SourceCount;
    double TimeStage;
    double TimeStep;
    Node * Nodes;
    double *Amplitude;

    int GetWidth();
    int GetHeight();
    bool GetBinaryData(int x, int y);
    double GetNormalizedData(int x, int y);

    void Iterate();
    void KeyPressed(KeyCode key);
private:
    void ReinitGrid(int width, int height);
    void DeinitGrid();
    double GetAmplitude(int x, int y);
    int SetAmplitude(int x, int y, double value);
};
} // namespace
#endif //MODEL_H
