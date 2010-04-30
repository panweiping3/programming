#ifndef _SB_HTTP_H_
#define _SB_HTTP_H_

#include <QObject>
#include <QDebug>

class QUrl;
class QHttp;
class QFile;
class QHttpRequestHeader;
class QHttpResponseHeader;

class SBHttp : public QObject
{
Q_OBJECT

public:
    SBHttp (QObject *parent = 0);
    ~SBHttp();
    void get(const QUrl &url, const QString &file);
    void post(const QUrl &url, const QString &file);
    void post_start(const QUrl &url, const QString &fileName, int port = 80);
    void post_end(void);
    void post_data(const char *buf, quint64 size);

public slots:
    void on_http_requestFinished(int id, bool error);
    void on_http_requestStarted(int id);
    void on_http_responseHeaderReceived(const QHttpResponseHeader &resp);

signals:
    void finished();

private slots:
    void done(bool error);
    void readAll(const QHttpResponseHeader &);

private:
    QHttp *http_p;
    QHttpRequestHeader *http_request_header;
    QFile *downloadFile;
    QByteArray http_send_bytes;
};

#endif

