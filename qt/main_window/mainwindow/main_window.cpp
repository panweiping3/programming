#include <QtGui>
//#include "finddialog.h"
//#include "gotocelldialog.h"
#include "main_window.h"
//#include "sortdialog.h"
//#include "spreadsheet.h"

MainWindow::MainWindow()
{
	spreadsheet = new Spreadsheet;
	setCentralWidget(spreadsheet);
	createActions();
	createMenus();
	createContextMenu();
	createToolBars();
	createStatusBar();
	readSettings();
	
	findDialog = 0;
	setWindowIcon(QIcon(":/images/icon.jpg"));
	setCurrentFile("");
}

