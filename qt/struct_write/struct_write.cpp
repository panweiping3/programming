#include <QApplication>
#include <QtGui>
#include <QDir>
#include <QFile>
#include <QDebug>

#include <string.h>

typedef char FILE_UUID[40];
typedef char HOST_UUID[40];
struct big_file_entry {
	qint16 flag;		// this entry is valid/invalid
	qint16 sign;		// this entry contains meta/file data
	qint32 offset;		// the offset of data
	qint64 size;		// the size of data
	FILE_UUID   file_uuid;	// 40
	HOST_UUID   host_uuid;	// 40
	qint8 pad[32];		// padding to 128 B
};

const QString TMPFILE = "./pwp";

int main(int argc, char *argv[])
{
	QFile file(TMPFILE);
	if (!file.open(QIODevice::WriteOnly)) {
		return -1;
	}
	
	struct big_file_entry *entry = (struct big_file_entry *)malloc(sizeof(struct big_file_entry));
	entry->flag = 89;
	entry->sign = 20;
	entry->offset = 235455;
	entry->size = 244445;
	memcpy(entry->file_uuid, "aaaaaaaaaaaa", 40);
	memcpy(entry->host_uuid, "bbbbbbbbbbbb", 40);
	
	for (int i=0; i<32; ++i) {
		entry->pad[i] = 0;
	}

	QDataStream out(&file);   
	out.writeRawData((const char *)entry, sizeof(struct big_file_entry));
	
	free(entry);

	file.close();
	if (!file.open(QIODevice::ReadOnly)) {
		return -1;
	}

	entry = (struct big_file_entry *)malloc(sizeof(struct big_file_entry));
	QDataStream in(&file);
	in.readRawData((char *)entry, sizeof(struct big_file_entry));
	
	file.close();

	return 0;
}
