#ifndef ENTERNAME_H
#define ENTERNAME_H

#include <QDialog>

namespace Ui {
class enterName;
}

class enterName : public QDialog
{
    Q_OBJECT

public:
    explicit enterName(QWidget *parent = 0);
    ~enterName();

signals:
    void sendData(QString str);

private slots:
    void on_lineEdit_editingFinished();

    //void on_buttonBox_clicked(QAbstractButton *button);

    void on_Ok_clicked();

private:
    Ui::enterName *ui;
};

#endif // ENTERNAME_H
