#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>

#include "cannonfield.h"
#include "gameboard.h"
#include "lcdrange.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{
	QPushButton *quit = new QPushButton(tr("&Quit"));
	quit->setFont(QFont("Times", 18, QFont::Bold));

	connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

	LCDRange *angle = new LCDRange(tr("angle"));
	angle->setRange(5, 70);

	LCDRange *force = new LCDRange(tr("force"));
	force->setRange(10, 50);

	QFrame *cannonBox = new QFrame;
	cannonBox->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	
	cannonField = new CannonField;
	
	connect(angle, SIGNAL(valueChanged(int)), cannonField, SLOT(setAngle(int)));
	connect(cannonField, SIGNAL(angleChanged(int)), angle, SLOT(setValue(int)));

	connect(force, SIGNAL(valueChanged(int)), cannonField, SLOT(setForce(int)));
	connect(cannonField, SIGNAL(forceChanged(int)), force, SLOT(setValue(int)));

	connect(cannonField, SIGNAL(hit()), this, SLOT(hit()));
	connect(cannonField, SIGNAL(missed()), this, SLOT(missed()));

	QPushButton *shoot = new QPushButton(tr("&Shoot"));
	shoot->setFont(QFont("Times", 18, QFont::Bold));
	connect(shoot, SIGNAL(clicked()), this, SLOT(fire()));
	connect(cannonField, SIGNAL(canShoot(bool)), shoot, SLOT(setEnabled(bool)));

	QPushButton *restart = new QPushButton(tr("&New Game"));
	restart->setFont(QFont("Times", 18, QFont::Bold));
	connect(restart, SIGNAL(clicked()), this, SLOT(newGame()));

	hits = new QLCDNumber(2);
	hits->setSegmentStyle(QLCDNumber::Filled);
	
	shotsLeft = new QLCDNumber(2);
	shotsLeft->setSegmentStyle(QLCDNumber::Filled);
	
	QLabel *hitsLabel = new QLabel(tr("Hits"));
	QLabel *shotsLeftLabel = new QLabel(tr("Shots left"));


	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(shoot);	
	topLayout->addWidget(hits);	
	topLayout->addWidget(hitsLabel);	
	topLayout->addWidget(shotsLeft);	
	topLayout->addWidget(shotsLeftLabel);	
	topLayout->addStretch(1);
	topLayout->addWidget(restart);	

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addWidget(angle);
	leftLayout->addWidget(force);

	QGridLayout *grid = new QGridLayout;

	grid->addWidget(quit, 0, 0);
	grid->addLayout(topLayout, 0, 1);
	grid->addLayout(leftLayout, 1, 0);
	grid->addWidget(cannonField, 1, 1, 2, 1);
	grid->setColumnStretch(1, 10);
	setLayout(grid);

	angle->setValue(60);
	force->setValue(25);
	angle->setFocus();

	newGame();
}

void GameBoard::fire()
{
	if (cannonField->gameOver() || cannonField->isShooting())
		return;

	shotsLeft->display(shotsLeft->intValue() - 1);
	cannonField->shoot();
}

void GameBoard::hit()
{
	hits->display(hits->intValue() + 1);
	
	if (shotsLeft->intValue() == 0)
		cannonField->setGameOver();
	else
		cannonField->newTarget();
}

void GameBoard::missed()
{
	if (shotsLeft->intValue() == 0)
		cannonField->setGameOver();
}

void GameBoard::newGame()
{
	shotsLeft->display(15);
	hits->display(0);
	cannonField->restartGame();
	cannonField->newTarget();
}	
