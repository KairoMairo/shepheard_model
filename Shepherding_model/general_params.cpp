#include "general_params.h"
#include "ui_general_params.h"

#include "model/algorithm.h"

CGeneralParams::CGeneralParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGeneralParams)
{
    ui->setupUi(this);
}

CGeneralParams::~CGeneralParams()
{
    delete ui;
}

void CGeneralParams::take_general_params()
{
    CAlgorithm::algorithm.set_gen_center(QPoint(ui->x_agent->value(), ui->y_agent->value()));
    CAlgorithm::algorithm.set_gen_size(QPoint(ui->gen_lenght->value(), ui->gen_width->value()));
    CAlgorithm::algorithm.set_goal(QPoint(ui->x_goal->value(), ui->y_goal->value()));
}

void CGeneralParams::on_lenght_valueChanged(double arg1)
{
    ui->gen_lenght->setMaximum(arg1);
    ui->x_agent->setMaximum(arg1);
    ui->x_goal->setMaximum(arg1);

    emit change_lenght(arg1);
}

void CGeneralParams::on_width_valueChanged(double arg1)
{
    ui->gen_width->setMaximum(arg1);
    ui->y_agent->setMaximum(arg1);
    ui->y_goal->setMaximum(arg1);

    emit change_width(arg1);
}
