#include "shepherd.h"

#define SIZE 2

CShepherd::CShepherd()
{
    speed       = 1.5;
    size        = SIZE;
    blind_angle = 0;
}

void CShepherd::set_blind_angle(int blind_angle)
{
    if (blind_angle >= 0 && blind_angle <= 360)
    {
        this->blind_angle = blind_angle;
    }
}

int CShepherd::get_blind_angle()
{
    return blind_angle;
}
