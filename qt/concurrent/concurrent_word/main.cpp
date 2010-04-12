#include <QList>
#include <QMap>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QTime>
#include <QDebug>

#include <qtconcurrentmap.h>

#ifndef QT_NO_CONCURRENT
using namespace QtConcurrent;

QStringList findFiles(const QString &startDir, QStringList filters)
{
	QStringList names;
	QDir dir(startDir);

	foreach (QString file, dir.entryList(filters, QDir::Files))
		names += startDir + "/" + file;
	
	foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
		names += findFiles(startDir + "/" + subdir, filters);

	return names;
}

typedef QMap<QString, int> WordCount;

WordCount singleTreadedWordCount(QStringList files)
{
	WordCount wordCount;
	
	foreach (QString file, files)
	{
		QFile f(file);
		f.open(QIODevice::ReadOnly);
		QTextStream textStream(&f);
		
		while (textStream.atEnd() == false)
			foreach (QString word, textStream.readLine().split(" "))
				wordCount[word] += 1;
	}
	
	return wordCount;
}

WordCount countWords(const QString &file)
{
	QFile f(file);
	f.open(QIODevice::ReadOnly);
	QTextStream textStream(&f);
	WordCount wordCount;
	
	while (textStream.atEnd() == false)
		foreach (QString word, textStream.readLine().split(" "))
			wordCount[word] += 1;

	return wordCount;
}

void reduce(WordCount &result, const WordCount &w)
{
	QMapIterator<QString, int> i(w);
	while (i.hasNext())
	{
		i.next();
		result[i.key()] += i.value();
	}
}

int main()
{
	qDebug() << "发现finding files...";
	QStringList files = findFiles("/home/pwp/programming/", QStringList() << "*.cpp" << "*.h");
	qDebug() << files.count() << "files";
	
	qDebug() << "warmup";
	{
		QTime time;
		time.start();
		WordCount total = singleTreadedWordCount(files);
	}

	qDebug() << "warmup done";
	int singleThreadTime = 0;
	{
		QTime time;
		time.start();
		WordCount total = singleTreadedWordCount(files);
		singleThreadTime = time.elapsed();
		qDebug() << "single thread" << singleThreadTime;
	}

	int mapReduceTime = 0;
	{
		QTime time;
		time.start();
		WordCount total = mappedReduced(files, countWords, reduce);
		mapReduceTime = time.elapsed();
		qDebug() << "MapReduce" << mapReduceTime;
	}
	
	qDebug() << "MapReduce speedup x" << 1 + ((double)singleThreadTime - (double)mapReduceTime) / (double) mapReduceTime;
}

#else

int main()
{
	qDebug() << "Qt concurrent is not yet supported";
}

#endif
