#include "visual_window.h"
#include "ui_visual_window.h"

#include "model/algorithm.h"

#include <QColorDialog>
#include <QPalette>
#include <QPainter>
#include <QPen>

CVisualWindow::CVisualWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CVisualWindow)
{
    ui->setupUi(this);

    ui->goal->setAutoFillBackground(true);
    ui->agent->setAutoFillBackground(true);
    ui->shepherd->setAutoFillBackground(true);
    ui->other->setAutoFillBackground(true);

    set_color(this, QColor(0, 0, 0));
    set_color(ui->field, QColor(0, 0, 0));
    set_color(ui->goal, QColor(76, 255, 0));
    set_color(ui->agent, QColor(0, 85, 255));
    set_color(ui->shepherd, QColor(255, 255, 0));
    set_color(ui->other, QColor(255, 0, 0));

}

CVisualWindow::~CVisualWindow()
{
    delete ui;
}

void CVisualWindow::set_field_length(int length)
{
    ui->field->setFixedWidth(length);
}

void CVisualWindow::set_field_width(int width)
{
    ui->field->setFixedHeight(width);
}

void CVisualWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int down = ui->field->geometry().bottom();
    int left = ui->field->geometry().left();
    int size = 0;
    QPoint position;

    painter.setPen(QPen(QBrush(ui->other->palette().color(ui->other->backgroundRole())), 1));
    painter.setBrush(QBrush(ui->other->palette().color(ui->other->backgroundRole())));

    QList<COtherObject*> objects = CAlgorithm::algorithm.get_objects();

    while (!objects.isEmpty())
    {
        position = objects.first()->get_position();
        position.setY(down - position.y());
        position.setX(left + position.x());
        size = objects.first()->get_size();
        painter.drawEllipse(position, size, size);

        objects.takeFirst();
    }

    painter.setPen(QPen(QBrush(ui->goal->palette().color(ui->goal->backgroundRole())), 1));
    painter.setBrush(QBrush(ui->goal->palette().color(ui->goal->backgroundRole())));
    position = CAlgorithm::algorithm.get_goal();
    position.setX(left + position.x());
    position.setY(down - position.y());
    size = CAlgorithm::algorithm.get_goal_radius();
    painter.drawEllipse(position, size, size);

    painter.setPen(QPen(QBrush(ui->agent->palette().color(ui->agent->backgroundRole())), 1));
    painter.setBrush(QBrush(ui->agent->palette().color(ui->agent->backgroundRole())));

    QList<QPoint> positions = CAlgorithm::algorithm.get_agents_positions();

    while(!positions.isEmpty())
    {
        position = positions.takeFirst();
        position.setY(down - position.y());
        position.setX(left + position.x());
        painter.drawEllipse(position, 2, 2);
    }

    painter.setPen(QPen(QBrush(ui->shepherd->palette().color(ui->shepherd->backgroundRole())), 1));
    painter.setBrush(QBrush(ui->shepherd->palette().color(ui->shepherd->backgroundRole())));
    position = CAlgorithm::algorithm.get_shepherd_position();
    position.setY(down - position.y());
    position.setX(left + position.x());
    painter.drawEllipse(position, 2, 2);
}

void CVisualWindow::on_goal_clicked()
{
    change_color(ui->goal);
}

void CVisualWindow::change_color(QWidget *widget)
{
    QColor color = QColorDialog::getColor(widget->palette().color(widget->backgroundRole()));

    if (!color.isValid() )
    {
        return;
    }

    set_color(widget, color);
}

void CVisualWindow::set_color(QWidget *widget, QColor color)
{
    QPalette p = widget->palette();
    p.setColor(widget->backgroundRole(), color);
    widget->setPalette(p);
}

void CVisualWindow::on_shepherd_clicked()
{
    change_color(ui->shepherd);
}

void CVisualWindow::on_agent_clicked()
{
    change_color(ui->agent);
}

void CVisualWindow::on_other_clicked()
{
    change_color(ui->other);
}
