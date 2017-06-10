#include "other_object.h"

COtherObject::COtherObject()
{

}

void COtherObject::set_name(QString name)
{
    this->name = name;
}

QString COtherObject::get_name()
{
    return name;
}
