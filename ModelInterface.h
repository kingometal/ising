#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include "keycodes.h"

class ModelInterface
{
public:
    ModelInterface() = default;
    virtual ~ModelInterface() = default;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
    virtual bool GetBinaryData(int x, int y) = 0;
    virtual int GetData(int x, int y) = 0;

    virtual void Iterate() = 0;
    virtual void KeyPressed(KeyCode key) = 0;
};

#endif // MODELINTERFACE_H
