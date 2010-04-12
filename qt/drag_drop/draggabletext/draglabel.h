#ifndef DRAGABLE_TEXT 
#define DRAGABLE_TEXT

#include <QLabel> 

class DragLabel : public QLabel
{
	public:
		DragLabel(const QString &text, QWidget *parent);
	
	protected:
		void mousePressEvent(QMouseEvent *event);

	private:
		QString labelText;
};

#endif
