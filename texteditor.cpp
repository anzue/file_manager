#include <QTextStream>
#include <QDesktopServices>

#include "texteditor.h"
#include "ui_texteditor.h"

#include "infopanel.h"

//#include <iostream>
//using std::cout;

using namespace std;

TextEditor::TextEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::close(){
    hide();

    //????????????
    this->~TextEditor();
}

int TextEditor::openFile(QFileInfo file){
    vector<QString> supported_suffixes;
     const char q[][10] = {
        "txt",
        "cpp",
        "html",
        "c",
        "h",
        "hpp"
    };
    for(int i=0;i<6;++i)
        supported_suffixes.push_back(q[i]);

    state = Default;
    if(!file.isFile())
        return 1;

    //cout<<"File opened for reading\n";

    if(!file.isReadable()){
        showInfo("Error reading file");
        close();
        return 2;
    }

    if(!file.isWritable()){
        state = ReadOnly;
    }


    if(
        std::find(
                supported_suffixes.begin(),
                supported_suffixes.end(),
                file.completeSuffix())
            == supported_suffixes.end())
    {
        //showInfo("This type of files is not supported\n");
        QDesktopServices::openUrl(QUrl(file.absoluteFilePath()));
        close();
        return 3;
    }

    text = file.absoluteFilePath();

    this->setWindowFilePath(file.absoluteFilePath());

    if(state == ReadOnly)
        this->setWindowTitle(file.absoluteFilePath() + "(Read only mode)" + " Text Editor");
    else
         this->setWindowTitle(file.absoluteFilePath() + " Text Editor");

    doc = new QFile(file.absoluteFilePath());
    if(doc->isWritable())
        doc->open(QIODevice::ReadWrite);
    else
        doc->open(QIODevice::ReadOnly);

    text = "";
    char temp[maxLineSize+1];
    do{
        doc->readLine(temp,maxLineSize);
        text+=(QString)(temp);
    }
    while(doc->canReadLine());

 //   ui->textEdit->setText(text);
    ui->textEdit->setPlainText(text);
    doc->close();

 //   cout<< "Readed\n";
 //   cout << text.toStdString() <<'\n';

    return 0;
}

void TextEditor::on_exitEditor_clicked()
{
    close();
}

void TextEditor::save(){
    if(doc == NULL)
        return;

    text = ui->textEdit->document()->toPlainText();

    if(doc->isOpen())
        doc->close();

    doc->open(QIODevice::WriteOnly);

    if (!doc->isWritable()){
        showInfo("Unable to save file.\nFile is in Read Only mode","Error 101");        return;
    }


    char temp[maxLineSize+1];
    int p = 0;
    int q = 0;
    while(p + q <text.length()){
        p = 0;
        do
        {
            temp[p] = text[q].toLatin1();
            ++p;++q;
        }
        while(p<maxLineSize && q<text.length());
        temp[p]='\0';
 //       cout<<"writing\n";
 //       cout<<temp<<'\n';
        doc->write(temp);
    }
    if(temp[p-1]!='\n'){
        temp[0] = '\n';
        temp[1] = '\0';
        doc->write(temp);
    }
    doc->close();
}

void TextEditor::on_saveText_clicked()
{
    if ( state == ReadOnly )
    {
        showInfo("Unable to save file.\nFile is in Read Only mode","Error 101");
        return;
    }

    save();
}

