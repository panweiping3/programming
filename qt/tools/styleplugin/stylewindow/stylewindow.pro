HEADERS	= stylewindow.h
SOURCES = stylewindow.cpp main.cpp

TARGET	= styleplugin

win32{
	debug:DESTDIR = ../debug/
	release:DESTDIR = ../release/
} else {
	DESTDIR = ./
}

