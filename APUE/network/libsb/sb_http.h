#ifndef _SB_HTTP_H_
#define _SB_HTTP_H_

#include <QObject>
#include <QDebug>
#include <QUrl>

class QHttp;
class QFile;
class QHttpRequestHeader;
class QHttpResponseHeader;

class SBHttp : public QObject
{
Q_OBJECT

public:
    SBHttp (QObject *parent = 0);
    SBHttp (const QUrl url, int port, QObject *parent = 0);
    ~SBHttp();
    void setUrl(const QUrl &url) { m_url = url; }
    QUrl &getUrl(void) { return m_url; }
    void setPort(int port) { m_port = port; }
    int getPort(void) { return m_port; }
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
    QUrl m_url;
    int m_port;
    QHttpRequestHeader *http_request_header;
    QFile *downloadFile;
    QByteArray http_send_bytes;
};

#endif

