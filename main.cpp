#include "manager.h"
#include <QApplication>

//#define DEBUG

#ifdef DEBUG
#include "texteditor.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef DEBUG
    TextEditor q;
    q.show();
#endif
    Manager w;
    w.show();
    return a.exec();
}
