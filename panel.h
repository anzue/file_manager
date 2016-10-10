#ifndef PANEL_H
#define PANEL_H

#include "QFileSystemModel"
#include "ui_manager.h"


class Panel
{
public:
    Panel();
    ~Panel();
    Panel(
            QFileSystemModel*,
            QFileSystemModel*,
            QTreeView*,
            QListView*,
            QLineEdit*,
            QPoint,
            QSize,
            QString path = "/");

    QFileSystemModel* getList();
    QFileSystemModel* getTree();

    QString getPath();

    void setPath(QString);

    QFileInfo getSelectedFile();

    void recalculateSize();
    void setSize(QSize);
    void setPosition(QPoint);

    void openFolder(QFileInfo);
    void openFile(QFileInfo);
    void open(QFileInfo);

    void hideTree();
    void showTree();
    void changeTreeMode();
    int isTreeHiden();

    void setOther(Panel*);

    void copyFile(QFileInfo );
    void deleteFile(QFileInfo );
    void renameFile(QFileInfo ,QString);

    void rename(QString);

    void newFolder(QString name);
    void newFile(QString name);

    const static int percentsForTree = 50;

protected:
    Panel* other;

    QFileSystemModel* tree;
    QFileSystemModel* list;

    QTreeView* treeView;
    QListView* listView;

    QLineEdit* adress;

    QSize size;
    QPoint position;
    QString path;
    int treeHiden;
};

#endif // PANEL_H

