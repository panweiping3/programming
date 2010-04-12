TEMPLATE	= lib
CONFIG		+= plugin
HEADERS		= simplestyle.h	simplestyleplugin.h
SOURCES		= simplestyle.cpp simplestyleplugin.cpp

TARGET		= simplestyleplugin

win32{
	debug:DESTDIR = ../debug/styles/
	release:DESTDIR = ../release/styles/
} else {
	DESTDIR = ../styles/
}


