/********************************************************************************
** Form generated from reading ui file 'gotoCell.ui'
**
** Created: Tue Sep 23 16:47:18 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GOTOCELL_H
#define UI_GOTOCELL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_Dialog
{
public:
    QWidget *verticalLayout;
    QVBoxLayout *vboxLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    QSize size(524, 326);
    size = size.expandedTo(Dialog->minimumSizeHint());
    Dialog->resize(size);
    verticalLayout = new QWidget(Dialog);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setGeometry(QRect(30, 40, 401, 181));
    vboxLayout = new QVBoxLayout(verticalLayout);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    lineEdit = new QLineEdit(verticalLayout);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    vboxLayout->addWidget(lineEdit);

    label = new QLabel(verticalLayout);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout->addWidget(label);

    pushButton_2 = new QPushButton(verticalLayout);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    vboxLayout->addWidget(pushButton_2);

    pushButton = new QPushButton(verticalLayout);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    vboxLayout->addWidget(pushButton);


    retranslateUi(Dialog);

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    lineEdit->setText(QApplication::translate("Dialog", "25", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "Enter your age", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("Dialog", "&quit", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("Dialog", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

#endif // UI_GOTOCELL_H
