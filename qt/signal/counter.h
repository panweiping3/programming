#include <QObject>

class Counter : public QObject
{
	Q_OBJECT

	public:
    	Counter();
		void setValue(int value);

 	signals:
     	void valueChanged(int newValue);

 	private:
     	int m_value;
};
