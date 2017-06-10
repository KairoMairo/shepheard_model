#ifndef VISUAL_WINDOW_H
#define VISUAL_WINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class CVisualWindow;
}

/*!
 * \brief Класс окна визуализации работы алгоритма
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 */
class CVisualWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CVisualWindow(QWidget *parent = 0);
    ~CVisualWindow();

signals:
    void paint(int time);

public slots:
    /*!
     * \brief Устанавливает длину поля для рисования
     * \param length Длина
     */
    void set_field_length(int length);

    /*!
     * \brief Устанавливает ширину поля для рисования
     * \param width Ширина
     */
    void set_field_width(int width);

protected:
    /*!
     * \brief Рисование
     */
    void paintEvent(QPaintEvent *);

private slots:
    /*!
     * \brief Изменяет цвет цели
     */
    void on_goal_clicked();

    /*!
     * \brief Изменяет цвет пастуха
     */
    void on_shepherd_clicked();

    /*!
     * \brief Изменяет цвет агентов
     */
    void on_agent_clicked();

    /*!
     * \brief Изменяет цвет преград
     */
    void on_other_clicked();

private:
    /*!
     * \brief Изменяет цвет элемента окна
     * \param widget Уквзатель на элемент
     */
    void change_color(QWidget* widget);

    /*!
     * \brief Устанавливает цвет элемента
     * \param widget Указатель на элемент
     * \param color Цвет
     */
    void set_color(QWidget* widget, QColor color);

private:
    Ui::CVisualWindow *ui;
};

#endif // VISUAL_WINDOW_H
