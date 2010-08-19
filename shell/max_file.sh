#! /bin/sh
i=0;
while true ; do
	touch $i
	RESULT=`echo $?`
	if [ "$RESULT"x != "0"x ] ;then
		echo "max file is:"$i
	fi
	echo $i" file has been created"
	i=`expr $i + 1` 
done

