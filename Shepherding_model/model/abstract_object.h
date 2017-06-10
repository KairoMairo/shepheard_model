#ifndef CABSTRACTOBJECT_H
#define CABSTRACTOBJECT_H

#include <QPoint>
#include <QVector2D>

/*!
 * \brief Родительский класс для всех объектов алгоритма
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * Данный класс содержит в себе свойства и методы,
 * характерные для всех объектов алгоритма
 */
class CAbstractObject
{
public:
    CAbstractObject();

    /*!
     * \brief Устанавливает позицию объекта
     * \param position Позиция в виде точки, которую необходимо установить объекту
     *
     * Переводит переданную позицию в вектор и устанавливет объекту
     */
    void    set_position(QPoint position);

    /*!
     * \brief Возвращает текущую позицию объекта
     * \return Позицию объекта в виде точки
     */
    QPoint  get_position();

    /*!
     * \brief Устанавливает позицию объекта
     * \param position Позиция, которую необходимо установить объекту
     */
    void        set_vector_position(QVector2D position);

    /*!
     * \brief Возвращает текущую позицию объекта
     * \return Позицию объекта в виде вектора
     */
    QVector2D   get_vector_position();

    /*!
     * \brief Устанавливает размер объекта
     * \param size Радиус объекта
     */
    void    set_size(int size);

    /*!
     * \brief Возвращает размер объекта
     * \return Радиус объекта
     */
    int     get_size();

protected:
    QVector2D   position; ///< Позиция объекта
    int         size; ///< Радиус объекта

};

#endif // CABSTRACTOBJECT_H
