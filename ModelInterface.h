#ifndef MODEL_INTERFACE_H
#define MODEL_INTERFACE_H

#include "KeyCodes.h"

class ModelInterface
{
public:
    ModelInterface() = default;
    virtual ~ModelInterface() = default;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
    virtual bool GetBinaryData(int x, int y) = 0;
    virtual bool GetBinaryData(int index) = 0;
    virtual int GetData(int x, int y) = 0;

    virtual void Iterate() = 0;
    virtual void KeyPressed(KeyCode key) = 0;
};

#endif // MODEL_INTERFACE_H
