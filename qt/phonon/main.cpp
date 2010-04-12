#include <QApplication>
#include <phonon>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
 	Phonon::MediaObject *music = Phonon::createPlayer(Phonon::MusicCategory,
								Phonon::MediaSource("aaa.wav"));
    music->play();
	return app.exec();
}
