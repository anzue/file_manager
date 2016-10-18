#include "panel.h"

#include "texteditor.h"

#include<iostream>
using std::cout;

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
    setPath(newPath);
    recalculateSize();

    history.clear();
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

    setPath(file.absoluteFilePath());
}

void Panel::setPath(QString newPath,bool change){

    QFileInfo file(newPath);
    if(!file.exists() || !file.isDir()){
        adress->setText(path);
        return;
    }
    if(change && path!=newPath)
        history.push_back(path);

    listView->setRootIndex(list->setRootPath(file.absoluteFilePath()));
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
    }
    else{
        treeView->show();
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

void Panel::setOther(Panel * q){
    other = q;
}

void Panel::copyFile(QFileInfo fileInfo){

    if(fileInfo == QFileInfo())
        fileInfo = getSelectedFile();

    QString filename =
            fileInfo.absoluteFilePath();

    QFile file(filename);

    file.open(QIODevice::ReadOnly);

    if(file.exists() && file.isOpen() && file.isReadable()){
        QString
                newFilename =
                    other->getPath() + "/" +
                    QFileInfo(file.fileName()).fileName();

        file.copy(newFilename);
    }
    file.close();


}

void Panel::deleteFile(QFileInfo fileInfo){
    if(fileInfo.isDir())
        QDir(fileInfo.absoluteFilePath()).removeRecursively();
    else
        QFile(fileInfo.absoluteFilePath()).remove();
}

void Panel::renameFile(QFileInfo fileInfo,QString newName){
    QString filename = fileInfo.absoluteFilePath();
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    file.rename(newName);
    file.close();
}

void Panel::newFolder(QString name){
    QDir dir(path);
    dir.mkdir(name);
}

void Panel::newFile(QString name){
    QFile file(path+"/"+name);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void Panel::rename(QString newName){
    if(newName.length()<=0)
        return;
    QFileInfo file = getSelectedFile();
    QDir dir(file.absoluteDir());
    dir.rename(file.absoluteFilePath()
               ,dir.absolutePath()+"/"+newName);
}

QFileInfo Panel::getSelectedFile(){
    return
            list->fileInfo(listView->selectionModel()->
                           currentIndex());

}

void Panel::back(){

    if(history.size()<=0)
        return;

    setPath(history[history.size()-1],0);
    history.pop_back();
}
