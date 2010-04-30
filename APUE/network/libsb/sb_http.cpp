#include <QFile>
#include <QTextStream>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QHttpResponseHeader>

#include "sb_http.h"
SBHttp::SBHttp(QObject *parent) : QObject(parent)   
{  
    downloadFile = NULL;
    http = new QHttp(this);  
    connect(http, SIGNAL(done(bool)), this, SLOT(done(bool)));
    connect(http, SIGNAL(readyRead(const QHttpResponseHeader &)),
            this, SLOT(readAll(const QHttpResponseHeader &)));

    connect(http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(on_http_requestFinished(int, bool)));
    connect(http, SIGNAL(requestStarted(int)),
            this, SLOT(on_http_requestStarted(int)));
    connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
            this, SLOT(on_http_responseHeaderReceived(const QHttpResponseHeader &)));
}

SBHttp::~SBHttp()
{
    delete http;
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
        qDebug() << http->errorString();
    } else {
        qDebug() << "successfully id: " << id;
        if (downloadFile) {
            downloadFile->close();
        }
    }
}

void SBHttp::post(const QUrl &url, const QString &file)
{
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
    http->setHost(url.host(), 80);
    http->request(header, bytes);
}

void SBHttp::get(const QUrl &url, const QString &file)  
{  
    downloadFile = new QFile(file);
    downloadFile->open(QIODevice::ReadOnly);

    http->setHost(url.host(), 80);
    qDebug() << url.path();
    http->get(url.path(), downloadFile);
    http->close();
}
  
void SBHttp::readAll(const QHttpResponseHeader &qrsh)
{
    QString sl = http->readAll();
    qDebug() << "SBHttp::readAll qrsh.toString : ";
    qDebug() << qrsh.toString();
    qDebug() << "--------------------------";
}

void SBHttp::done(bool error)  
{
    qDebug() << "SBHttp::done =============================";
    if(error) {
        qDebug() << "Error: " << qPrintable(http->errorString()) << endl;
    }

    emit finished();
}

