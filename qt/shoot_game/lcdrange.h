#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>

class QSlider;
class QLabel;

class LCDRange : public QWidget
{
	Q_OBJECT

	public:
		LCDRange(QWidget *parent = 0);
		LCDRange(const QString &text, QWidget *parent = 0);
		int value() const;
		QString text() const;

	public slots:
		void setValue(int value);
		void setRange(int minValue, int maxValue);
		void setText(const QString &text);
	signals:
		void valueChanged(int newValue);

	private:
		void init();

		QSlider *slider;
		QLabel *label;
};

#endif
