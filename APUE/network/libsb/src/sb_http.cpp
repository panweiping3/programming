#include <QFile>
#include <QTextStream>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QHttpResponseHeader>

#include "sb_http.h"

SBHttp::SBHttp(QObject *parent) 
    : QObject(parent),
      m_http_request_header(NULL),
      m_downloadFile(NULL)
{  
    m_http_send_bytes.clear();
    m_http_p = new QHttp(this);  
    connect(m_http_p, SIGNAL(done(bool)), this, SLOT(done(bool)));
    connect(m_http_p, SIGNAL(readyRead(const QHttpResponseHeader &)),
            this, SLOT(readAll(const QHttpResponseHeader &)));

    connect(m_http_p, SIGNAL(requestFinished(int, bool)),
            this, SLOT(on_http_requestFinished(int, bool)));
    connect(m_http_p, SIGNAL(requestStarted(int)),
            this, SLOT(on_http_requestStarted(int)));
    connect(m_http_p, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
            this, SLOT(on_http_responseHeaderReceived(const QHttpResponseHeader &)));
    m_http_request_header = new QHttpRequestHeader();
}

SBHttp::~SBHttp()
{
    delete m_http_p;
    delete m_http_request_header;
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
        qDebug() << m_http_p->errorString();
    } else {
        qDebug() << "successfully id: " << id;
        if (m_downloadFile) {
            m_downloadFile->close();
        }
    }
}

void SBHttp::post_start(const QUrl &url, const QString &fileName, int port)
{
    m_http_p->setHost(url.host(), port);

    m_http_request_header->setRequest("POST", url.path(), 1, 1);
    m_http_request_header->setValue("Host", url.host());
    m_http_request_header->setValue("Content-type", "multipart/form-data, boundary=AaB03x");
    m_http_request_header->setValue("Cache-Control", "no-cache");
    m_http_request_header->setValue("Accept","*/*");

    QByteArray name(fileName.toUtf8());
    m_http_send_bytes.append("--AaB03x\r\n");
    m_http_send_bytes.append("content-disposition: ");
    // cupfile is a keyword in up.html
    m_http_send_bytes.append("form-data; name=\"cupfile\"; filename=\"" + name + "\"\r\n");
    m_http_send_bytes.append("Content-Transfer-Encoding: binary\r\n");
    m_http_send_bytes.append("\r\n");
}

void SBHttp::post_end(void) 
{
    m_http_send_bytes.append("\r\n");
    m_http_send_bytes.append("--AaB03x--");
    int len = m_http_send_bytes.length();
    m_http_request_header->setContentLength(len);
    m_http_p->request(*m_http_request_header, m_http_send_bytes);
}

void SBHttp::post_data(const char *buf, quint64 size)
{
    m_http_send_bytes.append(buf, size);
}

void SBHttp::get(const QUrl &url, const QString &file)  
{  
    m_downloadFile = new QFile(file);
    m_downloadFile->open(QIODevice::ReadOnly);

    m_http_p->setHost(url.host(), 80);
    qDebug() << url.path();
    m_http_p->get(url.path(), m_downloadFile);
    m_http_p->close();
}
  
void SBHttp::readAll(const QHttpResponseHeader &qrsh)
{
    QString sl = m_http_p->readAll();
    qDebug() << "SBHttp::readAll qrsh.toString : ";
    qDebug() << qrsh.toString();
    qDebug() << "--------------------------";
}

void SBHttp::done(bool error)  
{
    qDebug() << "SBHttp::done =============================";
    if(error) {
        qDebug() << "Error: " << qPrintable(m_http_p->errorString()) << endl;
    }

    emit finished();
}

