#ifndef IGUI_HH
#define IGUI_HH

#include <QtGui>

class IGUI
{
public:
    virtual ~IGUI() {}
    virtual void setUpWin() = 0;
};

#endif // IGUI_HH
