#include "entername.h"
#include "ui_entername.h"

enterName::enterName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enterName)
{
    ui->setupUi(this);
    connect(ui->Ok, SIGNAL(clicked()), this, SLOT(on_Ok_clicked()));
}

enterName::~enterName()
{
    delete ui;
}

void enterName::on_lineEdit_editingFinished()
{

}



void enterName::on_Ok_clicked()
{
    emit sendData(ui->lineEdit->text());
}
