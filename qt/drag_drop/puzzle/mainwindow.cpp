#include "mainwindow.h"
#include "pieceslist.h"
#include "puzzlewidget.h"

#include <QtGui>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupMenus();
	setupWidgets();
	
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	setWindowTitle("Puzzle");
}
	
void MainWindow::openImage(const QString &path)
{
	QString fileName = path;
	
	if (fileName.isNull())
	{
		fileName = QFileDialog::getOpenFileName(this, "Open image", "", "Image files(*.png *jpg *bmp)");
	}

	if (fileName.isEmpty() == false)
	{
		QPixmap newImage;
		
		if (newImage.load(fileName) == false)
		{
			QMessageBox::warning(this, "Open image", "This image file couldn't be loaded", QMessageBox::Cancel);	
			
			return;
		}
	
		puzzleImage = newImage;
		setupPuzzle();
	}
}

void MainWindow::setupPuzzle()
{
	int size = qMin(puzzleImage.width(), puzzleImage.height());	
	
     puzzleImage = puzzleImage.copy((puzzleImage.width() - size)/2,
         							(puzzleImage.height() - size)/2, size, size)
									.scaled(IMAGE_SIZE, IMAGE_SIZE, 
									Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

     piecesList->clear();

     for (int y = 0; y < IMAGE_SIZE/PIECE_SIZE; ++y) 
	 {
         for (int x = 0; x < IMAGE_SIZE/PIECE_SIZE; ++x) 
		 {
             QPixmap pieceImage = puzzleImage.copy(x*PIECE_SIZE, y*PIECE_SIZE, PIECE_SIZE, PIECE_SIZE);
             piecesList->addPiece(pieceImage, QPoint(x, y));
         }
     }

     qsrand(QCursor::pos().x() ^ QCursor::pos().y());

     for (int i = 0; i < piecesList->count(); ++i) 
	 {
         if (int(2.0*qrand() / (RAND_MAX+1.0)) == 1) 
		 {
             QListWidgetItem *item = piecesList->takeItem(i);
             piecesList->insertItem(0, item);
         }
     }

     puzzleWidget->clear();

	 setWindowIcon(QIcon(puzzleImage));	
}
	
void MainWindow::setCompleted()
{
	QMessageBox::information(this, "Puzzle Completed", "Congratulations! Clicked Ok to restart", QMessageBox::Ok);	
	
	setupPuzzle();
}

void MainWindow::setupMenus()
{
	QMenu *fileMenu = menuBar()->addMenu("&File");
	
	QAction *openAction = fileMenu->addAction("&Open...");
	openAction->setShortcut(QKeySequence("Ctrl + O"));
	
	QAction *exitAction = fileMenu->addAction("E&xit");	
	exitAction->setShortcut(QKeySequence("Ctrl + Q"));
	
	QMenu *gameMenu = menuBar()->addMenu("&Game");
	
	QAction *restartAction = gameMenu->addAction("&Restart");

	connect(openAction, SIGNAL(triggered()), this, SLOT(openImage()));
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(restartAction, SIGNAL(triggered()), this, SLOT(setupPuzzle()));
}

void MainWindow::setupWidgets()
{
	QFrame *frame = new QFrame;
	QHBoxLayout *frameLayout = new QHBoxLayout(frame);

	piecesList = new PiecesList;
	puzzleWidget = new PuzzleWidget;
	
	connect(puzzleWidget, SIGNAL(puzzleCompleted()), this, SLOT(setCompleted()), Qt::QueuedConnection);
	
	frameLayout->addWidget(piecesList);
	frameLayout->addWidget(puzzleWidget);
	
	setCentralWidget(frame);
}
