#include "shepherd_params.h"
#include "ui_shepherd_params.h"

#include "model/algorithm.h"

CShepherdParams::CShepherdParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CShepherdParams)
{
    ui->setupUi(this);
}

CShepherdParams::~CShepherdParams()
{
    delete ui;
}

void CShepherdParams::take_shepherd_params()
{
    CAlgorithm::algorithm.gen_shepherd(QPoint(ui->x_shepherd->value(), ui->y_shepherd->value()));
    CAlgorithm::algorithm.set_shepherd_noise(ui->noise->value());
    CAlgorithm::algorithm.set_shepherd_speed(ui->speed->value());
    CAlgorithm::algorithm.set_virtual_shepherd(ui->virtual_shepherd->isChecked());
}

void CShepherdParams::set_shepherd_x_max(int x)
{
    ui->x_shepherd->setMaximum(x);
}

void CShepherdParams::set_shepherd_y_max(int y)
{
    ui->y_shepherd->setMaximum(y);
}
