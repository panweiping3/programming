#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget *window = new QWidget;
	window->setWindowTitle("Enter Your Age");
	QSpinBox *spinBox = new QSpinBox;
	QSlider *slider = new QSlider(Qt::Horizontal);
	spinBox->setRange(0, 130);
	slider->setRange(0, 130);
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	spinBox->setValue(35);
	
    int n = 1;

	QPushButton *pushButton= new QPushButton(QObject::tr("%n message(s)", "", n));
	QObject::connect(pushButton, SIGNAL(clicked()), &app, SLOT(quit()));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	layout->addWidget(pushButton);
	window->setLayout(layout);
	
	window->show();

QRect r(0, 0, 1280, 35);
QRegion g(35, 35, 1210, 942);

QRect result = g.intersected(r).boundingRect();
qDebug() << r;
qDebug() << g;
qDebug() << result;

	return app.exec();
}
