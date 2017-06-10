#ifndef CMOBILEOBJECT_H
#define CMOBILEOBJECT_H

#include "abstract_object.h"


/*!
 * \brief Класс для мобильных объектов алгоритма
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * Данный класс является наследником CAbstractObject и содержит дополнительные свойства
 * и методы для мобильных объектов
 */
class CMobileObject : public CAbstractObject
{
public:
    CMobileObject();

    /*!
     * \brief Устанавливает скорость объекта
     * \param speed Скорость
     */
    void    set_speed(double speed);

    /*!
     * \brief Возвращает скорость объекта
     * \return Скорость
     */
    double  get_speed();

protected:
    double      speed; ///< Скорость
};

#endif // CMOBILEOBJECT_H
