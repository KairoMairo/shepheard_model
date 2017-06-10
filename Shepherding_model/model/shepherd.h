#ifndef CSHEPHERD_H
#define CSHEPHERD_H

#include "mobile_object.h"

/*!
 * \brief Класс для управляющего объекта
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * Является наследником класса CMobileObject с дополнительными свойствами и методами,
 * характерными для управляющего объекта
 */
class CShepherd : public CMobileObject
{
public:
    CShepherd();

    /*!
     * \brief Устанавливает слепую зону для пастуха
     * \param blind_angle Угол слепой зоны сзади пастуха
     *
     * \warning Данный метод не используется в программе
     */
    void    set_blind_angle(int blind_angle);

    /*!
     * \brief Возвращает угол слепой зоны пастуха
     * \return Угол слепой зоны сзади пастуха
     *
     * \warning Данный метод не используется в программе
     */
    int     get_blind_angle();

private:
    int blind_angle; ///< Угол слепой зоны
};

#endif // CSHEPHERD_H
