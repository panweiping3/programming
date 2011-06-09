#! /bin/bash

A=2
B=4

if [ $A > $B ]
then
	echo "big?"
else
	echo "small?"
fi

if (( $A > $B ))
then
	echo "big?"
else
	echo "small?"
fi
