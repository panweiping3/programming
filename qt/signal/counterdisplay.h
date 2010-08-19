#include <QObject>
#include <QDebug>

class CounterDisplay : public QObject
{
	Q_OBJECT

	public:
    	CounterDisplay();

 	public slots:
     	void showValue(int value);
};
