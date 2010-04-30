#include <QApplication>
#include <QUrl>
#include <QLabel>
#include <QFile>
#include <QDebug>

//#include <libsb.h>
#include "../libsb.h"
//#include "../sb_http.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (argc != 2) {
        qDebug() << "./a.out file";
        exit(1);
    }
	QLabel *label = new QLabel("pwp");    
#if 0
    SBHttp *http = new SBHttp(label);
    http->post_start(QUrl("http://192.168.5.201:80/upact.php"), "example");

    QFile qFile("example");
    qFile.open( QIODevice::ReadOnly );
    QByteArray bytes = qFile.readAll();
    qFile.close(); 
    
    http->post_data(bytes.constData(), bytes.size());
    http->post_end();
#endif

#if 1
    int fd = open_network("http://192.168.5.201:80/upact.php", 80, HTTP);   
    if (fd < 0) {
        qDebug() <<__FILE__ << __LINE__ << __func__ << "open_network error";
        exit(1);
    }

    send_start(fd, argv[1]);

    QFile qFile(argv[1]);
    qFile.open( QIODevice::ReadOnly );
    QByteArray bytes = qFile.readAll();
    qFile.close(); 
    
    send_data(fd, bytes.constData(), bytes.size());
    
    send_end(fd);

    close_network(fd);
#endif
    label->resize(400, 300);
    label->show();
    return app.exec();
}

