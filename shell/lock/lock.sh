#! /bin/bash

lockfile important.lock
if [ $? = 0 ] 
then  
	echo "create lock file ok"
fi

sleep 10

rm -f important.lock
if [ $? = 0 ] 
then
	echo "delete lock file ok"
fi
