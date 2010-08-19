#! /bin/sh

KB=1024
UNIT=$KB
STEP=16
COUNT=1
MAX_COUNT=1048576
LOG_FILE="./time.log"
DATA_FILE="./data_"
DATA="aaa"
OFFSET="0"

rm $LOG_FILE
rm ./data_* -rf
touch $LOG_FILE

while [ $COUNT -lt $MAX_COUNT ]
do
	FILE=$DATA_FILE"$COUNT"
	dd if=/dev/zero of=$FILE bs=$UNIT count=$COUNT &>/dev/null
	echo "file name="$FILE >> $LOG_FILE
	SIZE=`expr $UNIT \* $COUNT`
	echo "file size="$SIZE >> $LOG_FILE
	echo "offset   =0" >> $LOG_FILE
	echo "data     ="$DATA  >> $LOG_FILE
	/usr/bin/time -ao $LOG_FILE ./main $FILE $OFFSET $DATA 
	echo " " >> $LOG_FILE
	echo " " >> $LOG_FILE
	rm $FILE
	COUNT=`expr $COUNT \* $STEP` 
done

