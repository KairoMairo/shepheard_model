#ifndef COTHEROBJECT_H
#define COTHEROBJECT_H

#include "abstract_object.h"

#include <QString>

/*!
 * \brief Класс для объектов-преград
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * Данный класс является наследником класса CAbstractObject
 * и содержит дополнительные методы и свойства, помогающие идентифицировать объекты
 */
class COtherObject : public CAbstractObject
{
public:
    COtherObject();

    /*!
     * \brief Устанавливает имя объекта
     * \param name Имя объекта в виде строки
     */
    void set_name(QString name);

    /*!
     * \brief Возвращает имя объекта
     * \return Имя объекта в виде строки
     */
    QString get_name();

private:
    QString name; ///< Имя объекта
};

#endif // COTHEROBJECT_H
