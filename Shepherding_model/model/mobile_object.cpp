#include "mobile_object.h"

#define SIZE 2

CMobileObject::CMobileObject()
{
    size = SIZE;
}

void CMobileObject::set_speed(double speed)
{
    if (speed > 0)
    {
        this->speed = speed;
    }
}

double CMobileObject::get_speed()
{
    return speed;
}
