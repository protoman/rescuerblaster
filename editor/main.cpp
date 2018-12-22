#include "mainwindow.h"
#include <QApplication>

std::string FILEPATH;

int main(int argc, char *argv[])
{
    std::string EXEC_NAME;
    #ifndef WIN32
        EXEC_NAME = "editor";
    #else
        EXEC_NAME = "editor.exe";
    #endif

    std::string argvString = std::string(argv[0]);
    FILEPATH = argvString.substr(0, argvString.size()-EXEC_NAME.size());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
