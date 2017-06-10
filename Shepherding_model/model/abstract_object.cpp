#include "abstract_object.h"

CAbstractObject::CAbstractObject()
{
    size        = 1;
}

void CAbstractObject::set_position(QPoint position)
{
    this->position.setX(position.x());
    this->position.setY(position.y());
}

QPoint CAbstractObject::get_position()
{
    return QPoint(position.x(), position.y());
}

void CAbstractObject::set_vector_position(QVector2D position)
{
    this->position = position;
}

QVector2D CAbstractObject::get_vector_position()
{
    return position;
}

void CAbstractObject::set_size(int size)
{
    if (size > 0)
    {
        this->size = size;
    }
}

int CAbstractObject::get_size()
{
    return size;
}
