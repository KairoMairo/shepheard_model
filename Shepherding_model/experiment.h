#ifndef CEXPERIMENT_H
#define CEXPERIMENT_H

#include <QThread>
#include <QList>

/*!
 * \brief Класс для проведения экспериментальных вычислений
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 */
class CExperiment : public QThread
{
    Q_OBJECT

public:
    CExperiment();

    /*!
     * \brief Выполняет эксперимент
     */
    void run();

signals:
    /*!
     * \brief Сигнал о завершении эксперимента
     */
    void finished();

private:
    /*!
     * \brief Сохранение результатов эксперимента в файл CSV
     */
    void save_data();

    /*!
     * \brief Обработка неудачного выполнения эксперимента
     */
    void fail();

    /*!
     * \brief Генерация преград
     */
    void random_objects();


private:
    int agent_quantity; ///< количество агентов
    int quantity; ///< количество проведенных экспериментов
    int fail_experiment; ///< количество неудачных экспериментов
    int middle_time; ///< среднее время выполнения алгоритма

    QList<int> time; ///< Список результатов эксперимента
    QList<int> fails; ///< Список неудачных экспериментов
};

#endif // CEXPERIMENT_H
