#include "manager.h"

#include "infopanel.h"

//#include "ui_manager.h"

//#include "texteditor.h"

//#define WINDOWS

QPoint left_pos(5,5),
        right_pos(500,5);

QSize default_panel_size(490,490);

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);

    QString path = "/";

#ifdef WINDOWS
    path = "C:/";
#endif

    left = new Panel(
                new QFileSystemModel(this),
                new QFileSystemModel(this),
                ui->left_tree_view,
                ui->left_list_view,
                left_pos,
                default_panel_size,
                path);

    right = new Panel(
                new QFileSystemModel(this),
                new QFileSystemModel(this),
                ui->right_tree_view,
                ui->right_list_view,
                right_pos,
                default_panel_size,
                path);

}

Manager::~Manager()
{
    delete ui;
    delete left;
    delete right;
}

void Manager::on_left_tree_view_clicked(const QModelIndex &index)
{
    left->open(left->getTree()->fileInfo(index));
}

void Manager::on_right_tree_view_clicked(const QModelIndex &index)
{
    right->open(right->getTree()->fileInfo(index));
}

void Manager::on_left_list_view_clicked(const QModelIndex &index)
{
    index.isValid();
}

void Manager::on_right_list_view_clicked(const QModelIndex &index)
{
    index.isValid();
}

void Manager::on_left_list_view_doubleClicked(const QModelIndex &index)
{
    left->open(left->getTree()->fileInfo(index));
}

void Manager::on_right_list_view_doubleClicked(const QModelIndex &index)
{
    right->open(right->getTree()->fileInfo(index));
}

void Manager::on_actionAbout_program_triggered()
{
    showInfo("there will be info");
}

void Manager::on_actionHide_left_tree_triggered()
{
    left->hideTree();
}

void Manager::on_actionHide_right_tree_triggered()
{
    right->hideTree();
}

void Manager::on_actionShow_left_tree_triggered()
{
    left->showTree();
}

void Manager::on_actionShow_right_tree_triggered()
{
    right->showTree();
}

void Manager::on_actionHide_both_triggered()
{
    left->hideTree();
    right->hideTree();
}

void Manager::on_actionShow_both_triggered()
{
    left->showTree();
    right->showTree();
}