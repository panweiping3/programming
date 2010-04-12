#include <QImage>
#include <QList>
#include <QThread>
#include <QDebug>
#include <QtConcurrent>

#ifndef QT_NO_CONCURRENT

QImage scale(const QImage &image)
{
	qDebug() << "Scaling image in thread" << QThread::currentThread();
	return image.scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	const int imageCount = 40;
	QList<QImage> images;

	for (int i=0; i < imageCount; i++)
	{
		images.append(QImage(1600, 1200, QImage::Format_ARGB32_Premultiplied));
	}

	QList<QImage> thumbnails = QtConcurrent::blockingMapped(images, scale); 

	return 0;
}

#else
int main()
{
	qDebug() << "Qt Concurrent is not yet supported";
}
#endif
