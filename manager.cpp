#include "manager.h"

#include "infopanel.h"

#include "entername.h"

#include <QShortcut>

QPoint left_pos(5,5),
        right_pos(500,5);

QSize default_panel_size(490,490);

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);

    QString path = "/home/anton/Стільниця/Test/";

#ifdef WINDOWS
    path = "C:/";
#endif

    left = new Panel(
                new QFileSystemModel(this),
                new QFileSystemModel(this),
                ui->left_tree_view,
                ui->left_list_view,
                ui->leftAdress,
                left_pos,
                default_panel_size,
                path);

    right = new Panel(
                new QFileSystemModel(this),
                new QFileSystemModel(this),
                ui->right_tree_view,
                ui->right_list_view,
                ui->rightAdress,
                right_pos,
                default_panel_size,
                path);

    left->setOther(right);
    right->setOther(left);

    active = left;

    left->setPath(path);
    right->setPath(path);
    //ui->renameLeft->hide();
    //ui->renameRight->hide();
    //ui->newFileLeft->hide();

    confirm = new enterName(this);
    confirm->hide();

    connect(confirm, SIGNAL(sendData(QString)),this, SLOT(recieveData(QString)));

    //new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT(hide()));
    //new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(show()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT( on_actionHide_both_triggered() ));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT( on_actionShow_both_triggered() ));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT( on_actionHide_both_triggered() ));
    new QShortcut(QKeySequence(Qt::Key_F1), this ,SLOT( on_actionHelp_triggered() ));
    new QShortcut(QKeySequence(Qt::Key_F2), this ,SLOT( on_actionAbout_program_triggered() ));

    new QShortcut(QKeySequence(Qt::Key_F6) ,this ,SLOT(Move()));
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
    showInfo("File manager 1.0\nAutor - Zuev Anton\nYear 2016\n","About program");
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

void Manager::on_actionCopy_triggered()
{
    active->copyFile(active->getSelectedFile());
}

void Manager::on_right_tree_view_activated(const QModelIndex &index)
{
    active = right;
}

void Manager::on_right_list_view_activated(const QModelIndex &index)
{
    active = right;
}

void Manager::on_left_list_view_activated(const QModelIndex &index)
{
    active = left;
}

void Manager::on_left_tree_view_activated(const QModelIndex &index)
{
    active = left;
}

void Manager::on_copyLeft_clicked()
{
    left->copyFile(left->getSelectedFile());
}

void Manager::on_renameRight_clicked()
{
    active = right;
    mode = _RENAME;
    hide();
    confirm->show();
}

void Manager::on_moveLeft_clicked()
{
    left->copyFile(left->getSelectedFile());
    left->deleteFile(left->getSelectedFile());
}

void Manager::on_deleteLeft_clicked()
{
    left->deleteFile(left->getSelectedFile());
}

void Manager::on_editLeft_clicked()
{
    left->openFile(left->getSelectedFile());
}

void Manager::on_renameLeft_clicked()
{
    active = left;
    mode = _RENAME;
    hide();
    confirm->show();
}

void Manager::on_copyRight_clicked()
{
    right->copyFile(right->getSelectedFile());
}

void Manager::on_moveRight_clicked()
{
    right->copyFile(right->getSelectedFile());
    right->deleteFile(right->getSelectedFile());
}

void Manager::on_deleteRight_clicked()
{
    right->deleteFile(right->getSelectedFile());
}

void Manager::on_editRight_clicked()
{
    right->openFile(right->getSelectedFile());
}

void Manager::on_newFolderLeft_clicked()
{
    mode = _FOLDER;
    hide();
    confirm->show();
}

void Manager::on_newFileLeft_clicked()
{
    mode = _FILE;
    hide();
    confirm->show();
}

void Manager::on_leftAdress_editingFinished()
{
    left->setPath(ui->leftAdress->text());
}

void Manager::recieveData(QString str){

    confirm->hide();
    show();

    if(str.length() == 0)
        return;

    if(mode == _RENAME)
        active->rename(str);
    else
        if(mode == _FOLDER)
            active->newFolder(str);
        else
            active->newFile(str);
}



void Manager::on_newFolderRight_clicked()
{
    mode = _FOLDER;
    hide();
    confirm->show();
}

void Manager::on_newFileRight_clicked()
{
    mode = _FILE;
    hide();
    confirm->show();
}

void Manager::on_backLeft_clicked()
{
    left->back();
}

void Manager::on_backRight_clicked()
{
    right->back();
}

void Manager::on_actionHelp_triggered()
{

}

void Manager::Move(){



    if(active == left)
        on_moveLeft_clicked();
    else
        on_moveRight_clicked();
}
