#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <QDialog>

namespace Ui {
class InfoPanel;
}

class InfoPanel : public QDialog
{
    Q_OBJECT

public:
    explicit InfoPanel(QWidget *parent = 0);
    void setText(QString text);
    ~InfoPanel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InfoPanel *ui;
};

void showInfo(QString infoText,QString panelName = "Info");

#endif // INFOPANEL_H
