main:main.c
	cc `pkg-config --cflags --libs glib-2.0 gthread-2.0` main.c -o main

clean:
	rm main main.o -rf

#$ pkg-config --cflags glib-2.0
# -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include 
#$ pkg-config --libs glib-2.0
#  -L/usr/lib -lm -lglib-2.0  

#$ pkg-config --cflags --libs gthread-2.0
#$ pkg-config --cflags --libs gobject-2.0

#$ pkg-config --cflags --libs gmodule-no-export-2.0 
#$ pkg-config --cflags --libs gmodule-2.0 

