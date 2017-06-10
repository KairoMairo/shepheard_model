#ifndef CAGENT_H
#define CAGENT_H

#include "mobile_object.h"

/*!
 * \brief Класс для автономных агентов
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * Является наследником класса CMobileObject с дополнительными свойствами и методами,
 * характерными автономным агентам
 */
class CAgent : public CMobileObject
{
public:
    CAgent();

    /*!
     * \brief Устанавливает направление движения агента
     * \param direction Направление движения
     */
    void        set_direction(QVector2D direction);

    /*!
     * \brief Возвращает направление движения агента
     * \return Направление движения в виде вектора
     */
    QVector2D   get_direction();

private:
    QVector2D direction; ///< Текущее направление движения

};

#endif // CAGENT_H
