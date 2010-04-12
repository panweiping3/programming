/********************************************************************************
** Form generated from reading ui file 'sort_dialog.ui'
**
** Created: Tue Sep 23 18:10:31 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SORT_DIALOG_H
#define UI_SORT_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    QSize size(424, 545);
    size = size.expandedTo(Dialog->minimumSizeHint());
    Dialog->resize(size);
    groupBox = new QGroupBox(Dialog);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(31, 39, 261, 151));
    gridLayout = new QGridLayout(groupBox);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    comboBox = new QComboBox(groupBox);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));

    gridLayout->addWidget(comboBox, 0, 1, 1, 1);

    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    comboBox_2 = new QComboBox(groupBox);
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

    gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);

    pushButton = new QPushButton(Dialog);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(320, 230, 75, 26));
    pushButton->setCheckable(true);
    layoutWidget = new QWidget(Dialog);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(31, 196, 261, 321));
    vboxLayout = new QVBoxLayout(layoutWidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    groupBox_2 = new QGroupBox(layoutWidget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    label_3 = new QLabel(groupBox_2);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(11, 27, 72, 24));
    label_4 = new QLabel(groupBox_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(11, 87, 72, 24));
    comboBox_3 = new QComboBox(groupBox_2);
    comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
    comboBox_3->setGeometry(QRect(80, 30, 150, 22));
    comboBox_4 = new QComboBox(groupBox_2);
    comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
    comboBox_4->setGeometry(QRect(80, 90, 161, 22));

    vboxLayout->addWidget(groupBox_2);

    groupBox_3 = new QGroupBox(layoutWidget);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    label_5 = new QLabel(groupBox_3);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(11, 27, 54, 20));
    label_6 = new QLabel(groupBox_3);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(11, 83, 54, 20));
    comboBox_5 = new QComboBox(groupBox_3);
    comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
    comboBox_5->setGeometry(QRect(80, 30, 114, 22));
    comboBox_6 = new QComboBox(groupBox_3);
    comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
    comboBox_6->setGeometry(QRect(70, 80, 175, 22));

    vboxLayout->addWidget(groupBox_3);

    buttonBox = new QDialogButtonBox(Dialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(321, 128, 75, 61));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    retranslateUi(Dialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
    QObject::connect(pushButton, SIGNAL(toggled(bool)), groupBox_2, SLOT(setVisible(bool)));
    QObject::connect(pushButton, SIGNAL(toggled(bool)), groupBox_3, SLOT(setVisible(bool)));

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("Dialog", "Primary key", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "Column", 0, QApplication::UnicodeUTF8));
    comboBox->clear();
    comboBox->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8)
    );
    label_2->setText(QApplication::translate("Dialog", "Order", 0, QApplication::UnicodeUTF8));
    comboBox_2->clear();
    comboBox_2->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "Ascending", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Dialog", "Descending", 0, QApplication::UnicodeUTF8)
    );
    pushButton->setText(QApplication::translate("Dialog", "&More", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("Dialog", "&Secondary key", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Dialog", "Column", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Dialog", "Order", 0, QApplication::UnicodeUTF8));
    comboBox_3->clear();
    comboBox_3->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8)
    );
    comboBox_4->clear();
    comboBox_4->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "Ascending", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Dialog", "Descending", 0, QApplication::UnicodeUTF8)
    );
    groupBox_3->setTitle(QApplication::translate("Dialog", "&Tertiary key", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("Dialog", "Column", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("Dialog", "Order", 0, QApplication::UnicodeUTF8));
    comboBox_5->clear();
    comboBox_5->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8)
    );
    comboBox_6->clear();
    comboBox_6->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "Ascending", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Dialog", "Descending", 0, QApplication::UnicodeUTF8)
    );
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

#endif // UI_SORT_DIALOG_H
