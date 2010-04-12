#! /bin/bash

lockfile important.lock
if [ $? = 0 ] 
then  
	echo "create lock file ok"
else
	echo "create lock file error"
fi

rm -f important.lock

