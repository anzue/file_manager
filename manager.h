#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include <QFileSystemModel>

#include "ui_manager.h"

#include "panel.h"

namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();

private slots:
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

private:
    Ui::Manager *ui;

    Panel *left;
    Panel *right;

};

#endif // MANAGER_H
