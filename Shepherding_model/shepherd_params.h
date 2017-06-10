#ifndef SHEPHERD_PARAMS_H
#define SHEPHERD_PARAMS_H

#include <QDialog>

namespace Ui {
class CShepherdParams;
}

/*!
 * \brief Класс окна редактирования параметров пастуха
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * В окне данного класса задаются основные параметры пастуха
 */
class CShepherdParams : public QDialog
{
    Q_OBJECT

public:
    explicit CShepherdParams(QWidget *parent = 0);
    ~CShepherdParams();

public slots:
    /*!
     * \brief Передает параметры пастуха в алгоритм
     */
    void take_shepherd_params();

    /*!
     * \brief Устанавливает максимальное значение положения пастуха по оси x
     * \param x Максимальное значение x
     */
    void set_shepherd_x_max(int x);

    /*!
     * \brief Устанавливает максимальное значение полржения пастуха по оси y
     * \param y Максимальное значение y
     */
    void set_shepherd_y_max(int y);

private:
    Ui::CShepherdParams *ui;
};

#endif // SHEPHERD_PARAMS_H
