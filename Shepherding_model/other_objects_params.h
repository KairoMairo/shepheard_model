#ifndef COTHEROBJECTSPARAMS_H
#define COTHEROBJECTSPARAMS_H

#include <QDialog>

namespace Ui {
class COtherObjectsParams;
}

/*!
 * \brief Класс окна редактирования объектов-преград
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * В окне данного класса задаются основные параметры объектов-преград
 */
class COtherObjectsParams : public QDialog
{
    Q_OBJECT

public:
    explicit COtherObjectsParams(QWidget *parent = 0);
    ~COtherObjectsParams();

signals:
    /*!
     * \brief Сигнал об изменениях
     */
    void change();

private:
    /*!
     * \brief Выводит список объектов
     */
    void update_list();

private slots:
    /*!
     * \brief Добавляет новый объект
     */
    void on_add_clicked();

    /*!
     * \brief Изменяет параметры существующего объекта
     */
    void on_change_clicked();

    /*!
     * \brief Удаляет выбранный объект
     */
    void on_remove_clicked();

    /*!
     * \brief Обрабатывает выбор объекта из списка
     * \param index Номер выбранного объекта
     */
    void on_list_clicked(const QModelIndex &index);

private:
    Ui::COtherObjectsParams *ui;
};

#endif // COTHEROBJECTSPARAMS_H
