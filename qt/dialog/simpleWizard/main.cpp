#include <QApplication>
#include "wizard.h"

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    GuideWizard *wizard = new GuideWizard;
    wizard->setWindowTitle("QWizard");
    wizard->show();

    return app.exec();
}
