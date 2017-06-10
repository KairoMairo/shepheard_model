#ifndef GENERAL_PARAMS_H
#define GENERAL_PARAMS_H

#include <QDialog>

namespace Ui {
class CGeneralParams;
}

/*!
 * \brief Класс окна редактирования основных параметров алгоритма
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * В окне данного класса задаются основные параметры алгоритма
 */
class CGeneralParams : public QDialog
{
    Q_OBJECT

public:
    explicit CGeneralParams(QWidget *parent = 0);
    ~CGeneralParams();

signals:
    /*!
     * \brief Сигнал об изменении длины рабочего поля
     * \param lenght Новая длина поля
     */
    void change_lenght(int lenght);

    /*!
     * \brief Сигнал об изменении ширины рабочего поля
     * \param width Новая ширина рабочего поля
     */
    void change_width(int width);

public slots:
    /*!
     * \brief Передает основные параметры в алгоритм
     */
    void take_general_params();

private slots:
    /*!
     * \brief Изменение длины поля
     * \param arg1 Длина поля
     */
    void on_lenght_valueChanged(double arg1);

    /*!
     * \brief Изменение ширины поля
     * \param arg1 Ширина поля
     */
    void on_width_valueChanged(double arg1);

private:
    Ui::CGeneralParams *ui;
};

#endif // GENERAL_PARAMS_H
