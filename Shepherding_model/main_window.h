#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPointer>

#include "experiment.h"

namespace Ui {
class CMainWindow;
}

class CGeneralParams;
class CAgentParams;
class CShepherdParams;
class CVisualWindow;
class COtherObjectsParams;

/*!
 * \brief Класс главного окна программы
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 */
class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

signals:
    /*!
     * \brief Сигнал, призывающий к передаче параметров в алгоритм
     */
    void take_params();

    /*!
     * \brief Сигнал, призывающий нарисовать кадр работы алгоритма
     */
    void paint();

private slots:
    /*!
     * \brief Выход из программы
     */
    void on_action_exit_triggered();

    /*!
     * \brief Открыть окно визуализации
     */
    void on_action_visual_window_triggered();

    /*!
     * \brief Открыть окно редактирования основных параметров алгоритма
     */
    void on_action_global_param_window_triggered();

    /*!
     * \brief Открыть окно редактирования параметров агентов
     */
    void on_action_agents_param_window_triggered();

    /*!
     * \brief Открыть окно редактирования параметров пастуха
     */
    void on_action_shepherd_param_window_triggered();

    /*!
     * \brief Запустить алгоритм
     */
    void on_action_start_triggered();

    /*!
     * \brief Открыть окно редактирования объектов-преград
     */
    void on_action_other_triggered();

    /*!
     * \brief Повторный запуск алгоритма
     */
    void repeat_result();

private:
    /*!
     * \brief Загрузка дочернего окна
     * \param widget Указатель на загружаемое окно
     */
    void load_sub_window(QWidget* widget);

private:
    Ui::CMainWindow *ui;

    QPointer<CGeneralParams>        m_general_params; ///< Указатель на окно редактирования основных параметров
    QPointer<CAgentParams>          m_agent_params; ///< Указатель на окно редактирования параметров агентов
    QPointer<CShepherdParams>       m_shepherd_params; ///< Указатель на окно редактирования параметров пастуха
    QPointer<CVisualWindow>         m_visual_window; ///< Указатель на окно визуализации
    QPointer<COtherObjectsParams>   m_other_objects_params; ///< указатель на окно редактирования объектов преград

    CExperiment exp; ///< объект для проведения экспериментальных вычислений

    bool play; ///< Флаг работы алгоритма
};

#endif // MAIN_WINDOW_H
