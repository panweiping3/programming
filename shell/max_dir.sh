#! /bin/sh
i=0;
while true ; do
	mkdir $i
	RESULT=`echo $?`
	if [ "$RESULT"x != "0"x ] ;then
		echo "max dir is:"$i
		exit
	fi
	echo $i" dir has been created"
	i=`expr $i + 1` 
done

