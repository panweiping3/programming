#include <Phonon/MediaObject>
#include <Phonon/Path>
#include <Phonon/AudioOutput>
#include <Phonon/Global>

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QDirModel>
#include <QtGui/QColumnView>

class MainWindow : public QMainWindow
{
		Q_OBJECT
		public:
			MainWindow();

		private slots:
			void play(const QModelIndex &index);

		private:
			void delayedInit();

			QColumnView m_fileView;
			QDirModel m_model;

			Phonon::MediaObject *m_media;
};

MainWindow::MainWindow() : m_fileView(this), m_media(0)
{
		setCentralWidget(&m_fileView);
		m_fileView.setModel(&m_model);
		m_fileView.setFrameStyle(QFrame::NoFrame);

		connect(&m_fileView, SIGNAL(updatePreviewWidget(const QModelIndex &)), SLOT(play(const QModelIndex &)));
}

void MainWindow::play(const QModelIndex &index)
{
		delayedInit();
		m_media->setCurrentSource(m_model.filePath(index));
		m_media->play();
}

void MainWindow::delayedInit()
{
		if (!m_media) {
				m_media = new Phonon::MediaObject(this);
				Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
				createPath(m_media, audioOutput);
		}
}

int main(int argc, char **argv)
{
		QApplication app(argc, argv);
		QApplication::setApplicationName("Phonon Tutorial 2");
		MainWindow mw;
		mw.show();
		return app.exec();
}

#include "tutorial2.moc"
