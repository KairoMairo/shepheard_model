#include "agent.h"

CAgent::CAgent()
{

}

void CAgent::set_direction(QVector2D direction)
{
    this->direction = direction;
}

QVector2D CAgent::get_direction()
{
    return direction;
}
