#include <QApplication>
#include <QUrl>
#include <QLabel>
#include <QFile>

//#include <libsb.h>
#include "../sb_http.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
	QLabel *label = new QLabel("pwp");    
    SBHttp *http = new SBHttp(label);
    //http->get(QUrl("http://192.168.5.201:80/upact.php"));
    http->post_start(QUrl("http://192.168.5.201:80/upact.php"), "example");

    QFile qFile("example");
    qFile.open( QIODevice::ReadOnly );
    QByteArray bytes = qFile.readAll();
    qFile.close(); 
    
    http->post_data(bytes.constData(), bytes.size());
    http->post_end();
    
//    http->post(QUrl("http://192.168.5.201:80/upact.php"), "qt.rpm");
    
    label->resize(400, 300);
    label->show();
    return app.exec();
}

