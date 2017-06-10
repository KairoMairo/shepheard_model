#include "other_objects_params.h"
#include "ui_other_objects_params.h"

#include "model/algorithm.h"

#include <QStandardItemModel>

COtherObjectsParams::COtherObjectsParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::COtherObjectsParams)
{
    ui->setupUi(this);

    update_list();
}

COtherObjectsParams::~COtherObjectsParams()
{
    delete ui;
}

void COtherObjectsParams::update_list()
{
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    QList<COtherObject*> objects = CAlgorithm::algorithm.get_objects();

    while(!objects.isEmpty())
    {
        item = new QStandardItem(objects.first()->get_name());
        model->appendRow(item);

        objects.takeFirst();
    }

    ui->list->setModel(model);
}

void COtherObjectsParams::on_add_clicked()
{
    CAlgorithm::algorithm.add_object(ui->name->text(),
                                     QPoint(ui->x->value(), ui->y->value()),
                                     ui->radius->value());

    update_list();

    emit change();
}

void COtherObjectsParams::on_change_clicked()
{
    CAlgorithm::algorithm.change_object(ui->list->currentIndex().row(),
                                        ui->name->text(),
                                        QPoint(ui->x->value(), ui->y->value()),
                                        ui->radius->value());

    update_list();

    emit change();
}

void COtherObjectsParams::on_remove_clicked()
{
    CAlgorithm::algorithm.delete_object(ui->list->currentIndex().row());

    update_list();

    emit change();
}

void COtherObjectsParams::on_list_clicked(const QModelIndex &index)
{
    COtherObject* object = CAlgorithm::algorithm.get_object(index.row());

    ui->name->setText(object->get_name());
    ui->x->setValue(object->get_vector_position().x());
    ui->y->setValue(object->get_vector_position().y());
    ui->radius->setValue(object->get_size());
}
