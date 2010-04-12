#ifndef CHAT_H
#define CHAT_H

#include <QtCore/QStringList>
#include <QtDBus/QtDBus>
#include "ui_chatmainwindow.h"
#include "ui_chatsetnickname.h"

class ChatMainWindow : public QMainWindow, Ui::ChatMainWindow
{
    Q_OBJECT

    public:
        ChatMainWindow();
        ~ChatMainWindow();
        
        void rebuildHistory();
    signals:
        void message(const QString &nickname, const QString &text);
        void action(const QString &nickname, const QString &text);

    private slots:
        void messageSlot(const QString &nickname, const QString &text);
        void actionSlot(const QString &nickname, const QString &text);
        void textChangedSlot(const QString &newText);
        void sendClickedSlot();
        void changeNickname();
        void aboutQt();
        void exiting();

    private:
        QString m_nickname;
        QStringList m_messages;
};

class NicknameDialog : public QDialog, public Ui::NicknameDialog
{
    Q_OBJECT

    public:
        NicknameDialog(QWidget *parent  = 0);
};

#endif
