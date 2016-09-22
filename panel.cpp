#include "panel.h"

#include "texteditor.h"


Panel::Panel()
{
    tree = list = NULL;
}

Panel::Panel(
        QFileSystemModel* newTree,
        QFileSystemModel* newList,
        QTreeView* newTreeView,
        QListView* newListView,
        QLineEdit* newLineEdit,
        QPoint newPosition,
        QSize newSize,
        QString newPath
        )
{
    adress = newLineEdit;
    setPath(newPath);
    tree = newTree;
    list = newList;
    tree->setRootPath(newPath);
    list->setRootPath(newPath);
    tree->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    treeView = newTreeView;
    listView = newListView;

    treeView->setModel(tree);
    listView->setModel(list);

    position = newPosition;
    size = newSize;
    treeHiden = 0;

    treeView->setColumnHidden(0,0);
    treeView->setColumnHidden(1,1);
    treeView->setColumnHidden(2,1);
    treeView->setColumnHidden(3,1);

    treeView->setColumnWidth(0,size.width()*(percentsForTree-2)/100);

    recalculateSize();
}

Panel::~Panel(){
    delete tree;
    delete list;
    delete treeView;
    delete listView;

}

QFileSystemModel* Panel::getList(){
    return list;
}

QFileSystemModel* Panel::getTree(){
    return tree;
}

void Panel::openFolder(QFileInfo file){
    if(!file.isDir())
        return;

    listView->setRootIndex(list->setRootPath(file.absoluteFilePath()));
    setPath(file.absoluteFilePath());
}

void Panel::setPath(QString newPath){
    path = newPath;
    adress->setText(path);
}

void Panel::openFile(QFileInfo file){

    TextEditor *q = new TextEditor();
    if(q->openFile(file)==0)
        q->show();
}

void Panel::open(QFileInfo file){
    if ( file.isDir() )
        openFolder(file);
    else
        openFile(file);
}

void Panel::setSize(QSize newSize){
    size = newSize;
    recalculateSize();
}

void Panel::setPosition(QPoint newPosition){
    position = newPosition;
    recalculateSize();
}

void Panel::recalculateSize(){
    if(treeHiden){
        treeView->hide();
        listView->resize(size);
        listView->move(position);
    }
    else{
        treeView->show();
        treeView->resize(size.rwidth()*percentsForTree/100,size.rheight());
        listView->resize(size.rwidth()*(100-percentsForTree)/100,size.rheight());
        listView->move(position.rx()+treeView->size().rwidth(),position.ry());
    }
}

void Panel::hideTree(){
    treeHiden = 1;
    recalculateSize();
}

void Panel::showTree(){
    treeHiden = 0;
    recalculateSize();
}

int Panel::isTreeHiden(){
    return treeHiden;
}

QString Panel::getPath(){
    return path;
}
