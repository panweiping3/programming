#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "helper.h"

class QLabel;
class QWidget;

class Window : public QWidget
{
	Q_OBJECT;
	
	public:	
		Window();
	
	private:
		Helper helper;
};

#endif
