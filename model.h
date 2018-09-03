#ifndef MODEL_H
#define MODEL_H

//int *s, *sm;//das Gitter und zusaetzliche Arrays zur Mittelwertbildung
//int m;//Magnetisierung


class Model
{
public:
    Model();
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

    void SetGridWidth(int width);
    void SetGridHeight(int height);
    int InitModel();
    int SetLattice();
    void SetGrid(int width, int height);
};

#endif //MODEL_H
