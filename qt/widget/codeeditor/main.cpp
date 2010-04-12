#include "codeeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CodeEditor editor;
    editor.setWindowTitle("editor example");
    editor.show();

    return app.exec();
}
