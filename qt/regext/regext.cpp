
  
#include <QApplication>
#include <QtGui>
#include <QObject>
#include <QDebug>
#include <assert.h>

#define tr QString

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
    
    QFile cmdlineFile("/home/pwp/dt8_cmdline");
    cmdlineFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QTextStream cmdlineStream( &cmdlineFile );
    QString line = cmdlineStream.readLine();
    cmdlineFile.close();

//ro root=livedisk:/dev/sda3 livedisk_iso=/dt8.iso liveimg
    if ( line.contains("livedisk") ) {
        int start = line.indexOf(QString("/dev/"), 0);
        if (start == -1) {
            return 3;
        }

        int end = line.indexOf(QString(" "), start);
        if (end == -1) {
            return 5;
        }
        
        QString devpath; 
        for (int i = start; i < end; ++i) {
            devpath += line[i];
        }
        
    }

    return 0;
}
