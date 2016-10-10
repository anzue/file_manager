#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include <QFileSystemModel>

#include "ui_manager.h"

#include "panel.h"

#include "entername.h"


enum createMode{
    _FOLDER,_FILE,_RENAME
};

namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();


signals:



private slots:

    void recieveData(QString str);

    void on_left_tree_view_clicked(const QModelIndex &index);
    void on_left_list_view_clicked(const QModelIndex &index);
    void on_right_tree_view_clicked(const QModelIndex &index);
    void on_right_list_view_clicked(const QModelIndex &index);
    void on_left_list_view_doubleClicked(const QModelIndex &index);
    void on_right_list_view_doubleClicked(const QModelIndex &index);

    void on_actionAbout_program_triggered();
    void on_actionHide_left_tree_triggered();
    void on_actionHide_right_tree_triggered();
    void on_actionShow_left_tree_triggered();
    void on_actionShow_right_tree_triggered();
    void on_actionHide_both_triggered();
    void on_actionShow_both_triggered();

    void on_actionCopy_triggered();

    void on_right_tree_view_activated(const QModelIndex &index);
    void on_right_list_view_activated(const QModelIndex &index);
    void on_left_list_view_activated(const QModelIndex &index);
    void on_left_tree_view_activated(const QModelIndex &index);

    void on_copyLeft_clicked();
    void on_renameRight_clicked();
    void on_moveLeft_clicked();
    void on_deleteLeft_clicked();
    void on_editLeft_clicked();
    void on_renameLeft_clicked();
    void on_copyRight_clicked();
    void on_moveRight_clicked();
    void on_deleteRight_clicked();
    void on_editRight_clicked();

    void on_newFolderLeft_clicked();

    void on_leftAdress_editingFinished();


    void on_newFileLeft_clicked();

private:
    Ui::Manager *ui;

    Panel *left;
    Panel *right;
    Panel *active;

    enterName *confirm;
    createMode mode;

};

#endif // MANAGER_H
