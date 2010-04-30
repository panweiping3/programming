#include <QFile>
#include <QTextStream>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QHttpResponseHeader>

#include "sb_http.h"
SBHttp::SBHttp(QObject *parent) 
    : QObject(parent),
      http_request_header(NULL),
      downloadFile(NULL)
{  
    http_send_bytes.clear();
    http_p = new QHttp(this);  
    connect(http_p, SIGNAL(done(bool)), this, SLOT(done(bool)));
    connect(http_p, SIGNAL(readyRead(const QHttpResponseHeader &)),
            this, SLOT(readAll(const QHttpResponseHeader &)));

    connect(http_p, SIGNAL(requestFinished(int, bool)),
            this, SLOT(on_http_requestFinished(int, bool)));
    connect(http_p, SIGNAL(requestStarted(int)),
            this, SLOT(on_http_requestStarted(int)));
    connect(http_p, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
            this, SLOT(on_http_responseHeaderReceived(const QHttpResponseHeader &)));
    http_request_header = new QHttpRequestHeader();
}

SBHttp::~SBHttp()
{
    delete http_p;
}

void SBHttp::on_http_requestStarted(int id)
{
    qDebug() << "Request Started id: " << id;
}

void SBHttp::on_http_responseHeaderReceived(const QHttpResponseHeader &resp)
{
    qDebug() << "HTTP response header received toString: ";
    qDebug() << resp.toString();
}

void SBHttp::on_http_requestFinished(int id, bool error)
{
    qDebug() <<"Request Finished id : " << id;

    if (error) {
        qDebug() << "with errors";
        qDebug() << http_p->errorString();
    } else {
        qDebug() << "successfully id: " << id;
        if (downloadFile) {
            downloadFile->close();
        }
    }
}

void SBHttp::post(const QUrl &url, const QString &file)
{
#if 0
    QFile qFile(file);
    qDebug() << qFile.fileName();
    qFile.open( QIODevice::ReadOnly );

    qDebug() << "host: " << url.host() << ", path: "<< url.path() << ", port:" << url.port();

    QHttpRequestHeader header("POST", url.path());
    header.setValue("Host", url.host());
    header.setValue("Content-type", "multipart/form-data, boundary=AaB03x");
    header.setValue("Cache-Control", "no-cache");
    header.setValue("Accept","*/*");

    QByteArray byt(file.toUtf8());
    QByteArray bytes;
    bytes.append("--AaB03x\r\n");
    bytes.append("content-disposition: ");
    // cupfile is a keyword in up.html
    bytes.append("form-data; name=\"cupfile\"; filename=\"" + byt+ "\"\r\n");
    bytes.append("Content-Transfer-Encoding: binary\r\n");
    bytes.append("\r\n");
    bytes.append(qFile.readAll());

    qFile.close(); // the file is opened earlier in the code
    bytes.append("\r\n");
    bytes.append("--AaB03x--");
    int contentLength = bytes.length();
    header.setContentLength(contentLength);
    http_p->setHost(url.host(), 80);
    http_p->request(header, bytes);
#endif
}

void SBHttp::post_start(const QUrl &url, const QString &fileName, int port)
{
    http_p->setHost(url.host(), port);

    http_request_header->setRequest("POST", url.path(), 1, 1);
    http_request_header->setValue("Host", url.host());
    http_request_header->setValue("Content-type", "multipart/form-data, boundary=AaB03x");
    http_request_header->setValue("Cache-Control", "no-cache");
    http_request_header->setValue("Accept","*/*");

    QByteArray name(fileName.toUtf8());
    http_send_bytes.append("--AaB03x\r\n");
    http_send_bytes.append("content-disposition: ");
    // cupfile is a keyword in up.html
    http_send_bytes.append("form-data; name=\"cupfile\"; filename=\"" + name + "\"\r\n");
    http_send_bytes.append("Content-Transfer-Encoding: binary\r\n");
    http_send_bytes.append("\r\n");
}

void SBHttp::post_end(void) 
{
    http_send_bytes.append("\r\n");
    http_send_bytes.append("--AaB03x--");
    int len = http_send_bytes.length();
    http_request_header->setContentLength(len);
    http_p->request(*http_request_header, http_send_bytes);
}

void SBHttp::post_data(const char *buf, quint64 size)
{
    http_send_bytes.append(buf, size);
}

void SBHttp::get(const QUrl &url, const QString &file)  
{  
    downloadFile = new QFile(file);
    downloadFile->open(QIODevice::ReadOnly);

    http_p->setHost(url.host(), 80);
    qDebug() << url.path();
    http_p->get(url.path(), downloadFile);
    http_p->close();
}
  
void SBHttp::readAll(const QHttpResponseHeader &qrsh)
{
    QString sl = http_p->readAll();
    qDebug() << "SBHttp::readAll qrsh.toString : ";
    qDebug() << qrsh.toString();
    qDebug() << "--------------------------";
}

void SBHttp::done(bool error)  
{
    qDebug() << "SBHttp::done =============================";
    if(error) {
        qDebug() << "Error: " << qPrintable(http_p->errorString()) << endl;
    }

    emit finished();
}

