#ifndef WDIGETGALLERY_H
#define WDIGETGALLERY_H

#include <QtGui>

class WidgetGally : public QDialog
{
    Q_OBJECT

    public:
        WidgetGally(QWidget *parent = 0);

    private slots:
        void changeStyle(const QString &styleName);
        void changePalette();
        void advanceProgressBar();

    private:
        void createTopLeftGroupBox();
        void createTopRightGroupBox();
        void createBottomLeftGroupBox();
        void createBottomRightGroupBox();
        void createProgressBar();

        QPalette originalPalette;

        QLabel *styleLabel;
        QComboBox *styleComboBox;
        QCheckBox *useStylePaletteCheckBox;
        QCheckBox *disableWidgetsCheckBox;

        QGroupBox *topLeftGroupBox;
        QRadioButton *radioButton1;
        QRadioButton *radioButton2;
        QRadioButton *radioButton3;
        QCheckBox *checkBox;
    
        QGroupBox *topRightGroupBox;
        QPushButton *defaultPushButton;
        QPushButton *togglePushButton;
        QPushButton *flatPushButton;

        QTabWidget *bottomLeftTabWidget;
        QTableWidget *tableWidget;
        QTextEdit *textEdit;

        QGroupBox *bottomRightGroupBox;
        QLineEdit *lineEdit;
        QSpinBox *spinBox;
        QDateTimeEdit *dateTimeEdit;
        QSlider *slider;
        
        QScrollBar *scrollBar;
        QDial *dial;

        QProgressBar *progressBar;
};

#endif
