#include "main_window.h"
#include "ui_main_window.h"
#include "general_params.h"
#include "agent_params.h"
#include "shepherd_params.h"
#include "visual_window.h"
#include "other_objects_params.h"
#include "experiment.h"


#include "model/algorithm.h"

#include <QMdiSubWindow>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);


    connect(&exp, SIGNAL(finished()), this, SLOT(repeat_result()));
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_action_exit_triggered()
{
    this->close();
}

void CMainWindow::on_action_visual_window_triggered()
{
    if (m_visual_window)
    {
         return;
    }

    m_visual_window = new CVisualWindow(this);
    load_sub_window(m_visual_window);

    connect(this, SIGNAL(paint()), &(*m_visual_window), SLOT(repaint()));

    if (m_general_params)
    {
        connect(m_general_params, &CGeneralParams::change_lenght, m_visual_window, &CVisualWindow::set_field_length);
        connect(m_general_params, &CGeneralParams::change_width, m_visual_window, &CVisualWindow::set_field_width);
    }

    if (m_other_objects_params)
    {
        connect(&(*m_other_objects_params), SIGNAL(change()), &(*m_visual_window), SLOT(repaint()));
    }
}

void CMainWindow::on_action_global_param_window_triggered()
{
    if (m_general_params)
    {
        return;
    }

    m_general_params = new CGeneralParams(this);
    load_sub_window(m_general_params);
    connect(this, &CMainWindow::take_params, m_general_params, &CGeneralParams::take_general_params);

    if (m_visual_window)
    {
        connect(m_general_params, &CGeneralParams::change_lenght, m_visual_window, &CVisualWindow::set_field_length);
        connect(m_general_params, &CGeneralParams::change_width, m_visual_window, &CVisualWindow::set_field_width);
    }

    if (m_shepherd_params)
    {
        connect(m_general_params, &CGeneralParams::change_lenght, m_shepherd_params, &CShepherdParams::set_shepherd_x_max);
        connect(m_general_params, &CGeneralParams::change_width, m_shepherd_params, &CShepherdParams::set_shepherd_y_max);
    }
}

void CMainWindow::on_action_agents_param_window_triggered()
{
    if (!m_agent_params)
    {
        m_agent_params = new CAgentParams(this);
        load_sub_window(m_agent_params);
        connect(this, &CMainWindow::take_params, m_agent_params, &CAgentParams::take_agent_params);
    }
}

void CMainWindow::on_action_shepherd_param_window_triggered()
{
    if (m_shepherd_params)
    {
        return;
    }

    m_shepherd_params = new CShepherdParams(this);
    load_sub_window(m_shepherd_params);
    connect(this, &CMainWindow::take_params, m_shepherd_params, &CShepherdParams::take_shepherd_params);

    if (m_general_params)
    {
        connect(m_general_params, &CGeneralParams::change_lenght, m_shepherd_params, &CShepherdParams::set_shepherd_x_max);
        connect(m_general_params, &CGeneralParams::change_width, m_shepherd_params, &CShepherdParams::set_shepherd_y_max);
    }
}

void CMainWindow::on_action_start_triggered()
{
    emit take_params();

    CAlgorithm::algorithm.gen_agents();

    while(!CAlgorithm::algorithm.test_goal())
    {
        CAlgorithm::algorithm.execution();

        emit paint();
    }

    //exp.run();

}

void CMainWindow::load_sub_window(QWidget *widget)
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(widget->windowTitle());
    window->setWindowIcon(widget->windowIcon());
    window->show();
}

void CMainWindow::on_action_other_triggered()
{
    if (m_other_objects_params)
    {
        return;
    }

    m_other_objects_params = new COtherObjectsParams(this);
    load_sub_window(m_other_objects_params);

    if (m_visual_window)
    {
        connect(&(*m_other_objects_params), SIGNAL(change()), &(*m_visual_window), SLOT(repaint()));
    }
}

void CMainWindow::repeat_result()
{
    on_action_start_triggered();
}
