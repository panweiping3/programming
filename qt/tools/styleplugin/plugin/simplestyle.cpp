#include "simplestyle.h"

#include <QtGui>

void SimpleStyle::polish(QPalette &palette)
{
	palette.setBrush(QPalette::Button, Qt::yellow);
}


