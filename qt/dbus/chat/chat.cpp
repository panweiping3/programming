#include "chat.h"
#include "chat_adaptor.h"
#include "chat_interface.h"
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

static const QString CHAT_DBUS_SERVICE = "com.trolltech.chat";

ChatMainWindow::ChatMainWindow()
    :m_nickname(QLatin1String("nickname"))
{
    setupUi(this);
    sendButton->setEnabled(false);

    connect(messageLineEdit, SIGNAL(textChanged(QString)), this,  SLOT(textChangedSlot(QString)));
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendClickedSlot()));
    connect(actionChangeNickname, SIGNAL(triggered(bool)), this, SLOT(changeNickname()));
    connect(actionAboutQt, SIGNAL(triggered(bool)), this, SLOT(aboutQt()));
    connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(exiting()));

    new ChatAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/", this);

    com::trolltech::chat *iface;
    iface = new com::trolltech::chat(QString(), QString(), QDBusConnection::sessionBus(), this);
    //QDBusConnection::sessionBus().connect(QString(), QString(), "com.trolltech.chat", "message", this, SLOT(messageSlot(QString, QString)));
    connect(iface, SIGNAL(message(QString, QString)), this, SLOT(messageSlot(QString, QString)));
    connect(iface, SIGNAL(action(QString, QString)), this, SLOT(actionSlot(QString, QString)));
    
    NicknameDialog dialog;
    dialog.cancelButton->setVisible(false);
    dialog.exec();

    m_nickname = dialog.nickname->text().trimmed();
    emit action(m_nickname, QLatin1String("joins the chat"));
}

ChatMainWindow::~ChatMainWindow()
{
}

void ChatMainWindow::rebuildHistory()
{
    QString history = m_messages.join(QLatin1String("\n"));
    chatHistory->setPlainText(history);
}

void ChatMainWindow::messageSlot(const QString &nickname, const QString &text)
{
    QString msg(QLatin1String("<%1> %2"));
    msg = msg.arg(nickname, text);
    m_messages.append(msg);

    if (m_messages.count() > 100) {
        m_messages.removeFirst();
    }

    rebuildHistory();
}

void ChatMainWindow::actionSlot(const QString &nickname, const QString &text)
{
    QString msg(QLatin1String("* %1 %2"));
    msg = msg.arg(nickname, text);
    m_messages.append(msg);

    if (m_messages.count() > 100) {
        m_messages.removeFirst();
    }

    rebuildHistory();
}

void ChatMainWindow::textChangedSlot(const QString &newText)
{
    sendButton->setEnabled(!newText.isEmpty());
}

void ChatMainWindow::sendClickedSlot()
{
    //QDBusMessage msg = QDBusMessage::createSignal("/", "com.trolltech.chat", "message");
    //msg << m_nickname << messageLineEdit->text();
    //QDBusConnection::sessionBus().send(msg);
    emit message(m_nickname, messageLineEdit->text());
    messageLineEdit->setText(QString());
}

void ChatMainWindow::changeNickname()
{
    NicknameDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString old = m_nickname;
        m_nickname = dialog.nickname->text().trimmed();
        emit action(old, QString("is now known as %1").arg(m_nickname));
    }   
}

void ChatMainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void ChatMainWindow::exiting()
{
    emit action(m_nickname, QLatin1String("leaves the chat"));
}

NicknameDialog::NicknameDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cann't connect the D-Bus session bus.\n");
        return 1;
    }

    if (!QDBusConnection::sessionBus().registerService(CHAT_DBUS_SERVICE)) {
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));
        qDebug() << "chat service has been started!";
    }

    ChatMainWindow chat;
    chat.show();
    return app.exec();
}
