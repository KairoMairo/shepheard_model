#ifndef AGENT_PARAMS_H
#define AGENT_PARAMS_H

#include <QDialog>

namespace Ui {
class CAgentParams;
}

/*!
 * \brief Класс окна редактирования параметров агентов
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * В окне данного класса задаются параметры алгоритма, касающиеся агентов
 */
class CAgentParams : public QDialog
{
    Q_OBJECT

public:
    explicit CAgentParams(QWidget *parent = 0);
    ~CAgentParams();

public slots:
    /*!
     * \brief Передает параметры из формы в алгоритм
     */
    void take_agent_params();

private:
    Ui::CAgentParams *ui;
};

#endif // AGENT_PARAMS_H
