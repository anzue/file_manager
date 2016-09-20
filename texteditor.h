#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QDialog>

//???
//#include "ui_manager.h"

#include <QFileSystemModel>

enum EditorMod {
    Default,
    ReadOnly
};

namespace Ui {
class TextEditor;
}

class TextEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = 0);
    int openFile(QFileInfo);
    void close();
    ~TextEditor();

private slots:
    void on_exitEditor_clicked();

    void on_saveText_clicked();

    void save();
    //void on_saveButton_changed();

private:
    Ui::TextEditor *ui;
    QFileInfo file;
    QString text;
    QFile* doc;
    EditorMod state;
    const static int maxLineSize = 100;
};

#endif // TEXTEDITOR_H
