#include "experiment.h"
#include "model/algorithm.h"

#include <QFile> // Подключаем класс QFile
#include <QTextStream> // Подключаем класс QTextStream
#include <QTime>
#include <QMessageBox>
#include <QTextStream>

#define QUANTITY 1
#define OBJECTS 4
#define OBJECT_RADIUS 30


CExperiment::CExperiment()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    /// Устанавливаем начальные значения свойств класса
    agent_quantity = 10;
    quantity = 0;
    fail_experiment = 0;
    middle_time = 1000;

    /// Разрешаем принудительную остановку потока
    setTerminationEnabled(true);
}

void CExperiment::run()
{
    QTime timer;

    /// Указываем файл для резервного копирования результатов эксперимента
    QFile fileOut("result.txt");

    /// Генерируем объекты-преграды
    //random_objects();

    /// Запускаем таймер
    timer.start();

    /// Начинаем выполнение алгоритма
    while(!CAlgorithm::algorithm.test_goal())
    {
        CAlgorithm::algorithm.execution();

        /// Если превышено время выполнения алгоритма, то считаем опыт неудачным
        if (timer.elapsed() > middle_time)
        {
            QMessageBox::information(0, "Информация", "Неудача!");
            save_data();

            fail_experiment++;

            emit finished();

            return;
        }
    }

    /// Если алгоритм успешно выполнился, то сохраняем время его выполнения
    int ms = timer.elapsed();

    time.push_back(ms);
    qSort(time.begin(), time.end());
    quantity++;
    save_data();

    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileOut);

        writeStream << QString("%1 %2").arg(quantity).arg(fail_experiment);

        fileOut.close();

    }


    if (quantity < QUANTITY)
    {
        emit finished();
    }
    else
    {
        QMessageBox::information(0, "Информация", "Алгоритм успешно выполнен.");
        quantity = 0;
        fails.push_back(fail_experiment);

        time.clear();
    }
}

void CExperiment::fail()
{
    fail_experiment++;
}

void CExperiment::random_objects()
{
    CAlgorithm::algorithm.clear_objects();

    CAlgorithm::algorithm.add_object("", QPoint(150, 200), OBJECT_RADIUS);
    CAlgorithm::algorithm.add_object("", QPoint(230, 100), OBJECT_RADIUS);
    CAlgorithm::algorithm.add_object("", QPoint(250, 250), OBJECT_RADIUS);
    CAlgorithm::algorithm.add_object("", QPoint(230, 270), OBJECT_RADIUS);


    /*

    int object_quantity = OBJECTS;

    QPoint position = CAlgorithm::algorithm.get_field_size();

    int x_max_position = position.x() - 100;
    int y_max_position = position.y() - 100;

    for (int i = 0; i < object_quantity; i++)
    {
        position.setX(qrand() % x_max_position + 100);
        position.setY(qrand() % y_max_position + 100);

        CAlgorithm::algorithm.add_object("", position, OBJECT_RADIUS);
    }*/

}

void CExperiment::save_data()
{
    QFile f("result.csv");

    if( f.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &f );

        QList<int>::Iterator i;

        /*for (i = time.begin(); i != time.end(); i++)
        {
            ts << QString("%1;\n").arg(*i);
        }*/

        for (i = fails.begin(); i != fails.end(); i++)
        {
            ts << QString("%1;\n").arg(*i);
        }

         f.close();
    }
}
