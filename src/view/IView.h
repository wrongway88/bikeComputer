#ifndef I_VIEW_H
#define I_VIEW_H

#include <memory>

#include "../utility/logging/logging.h"

#include "../data/ISensorData.h"

class IView
{
public:
    IView(){}
    virtual ~IView(){}

    virtual void init(int x, int y) = 0;

    virtual bool pushData(const std::shared_ptr<ISensorData>& data) = 0;

private:


};

#endif // I_VIEW_H
