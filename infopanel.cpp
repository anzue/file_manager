#include "infopanel.h"
#include "ui_infopanel.h"

InfoPanel::InfoPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoPanel)
{
    ui->setupUi(this);

}

InfoPanel::~InfoPanel()
{
    delete ui;
}

void InfoPanel::setText(QString text){
    ui->textBrowser->setText(text);
    show();
}

void InfoPanel::on_pushButton_clicked()
{
    close();
}

void showInfo(QString  infoText,QString panelName){
    InfoPanel *q = new InfoPanel();
    q->setText(infoText);
    q->setWindowTitle(panelName);
    q->show();
}
