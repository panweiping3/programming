#!/bin/bash 

# I want to know which partiiton dons the grub in mbr come from.
# Support both grub 0.97 and grub2

# global var to show where stage2 is
STAGE2_DEC_ADDRESS="1"

# INPUT: like /dev/sda /dev/sdb
# OUTPUT: return physical sector number of stage2, or 1 if stage 1.5

get_stage2_dec_address()
{
	TMP_DISK=$1
	TMP_FILE=first_sector
	dd if=$TMP_DISK of=$TMP_FILE bs=512 count=1 > /dev/null 2>&1

	ABSOLUTE_ADDRESS_HEX_0X44=` hexdump $TMP_FILE -s 0x44 -n 1 -e '"%02x"' `
	ABSOLUTE_ADDRESS_HEX_0X45=` hexdump $TMP_FILE -s 0x45 -n 1 -e '"%02x"' `
	ABSOLUTE_ADDRESS_HEX_0X46=` hexdump $TMP_FILE -s 0x46 -n 1 -e '"%02x"' `
	ABSOLUTE_ADDRESS_HEX_0X47=` hexdump $TMP_FILE -s 0x47 -n 1 -e '"%02x"' `
	# this indicate how to find stage2
	#   [7C44] --> Note: A very important location for anyone using GRUB!
	#              This (4-byte) Quad-Word contains the location of GRUB's
	#              stage2 file in sectors! You will always see the bytes
	#              01 00 00 00 in this location whenever GRUB has been
	#              installed in the first track (Sectors 1 ff.) of an HDD;
	#              immediately following the GRUB MBR in Absolute Sector 0.
	#     Example:
	#              DF 0A 93 01 (1930ADFh) [ "stage2 Sector" -> 26,413,791 ]
	#             [So, for this GRUB install, its stage2 file is located at
	#              Absolute Sector 26413791. This value will of course vary
	#              depending upon the physical location of the stage2 file!]

	STAGE2_HEX_ADDRESS="$ABSOLUTE_ADDRESS_HEX_0X47$ABSOLUTE_ADDRESS_HEX_0X46$ABSOLUTE_ADDRESS_HEX_0X45$ABSOLUTE_ADDRESS_HEX_0X44"
	rm $TMP_FILE -f

	# stage2 first sector
	STAGE2_DEC_ADDRESS=$(( 0x$STAGE2_HEX_ADDRESS ))
}

# INPUT: like /dev/sda /dev/sdb
# OUTPUT: return 1 if grub is installed, 0 else
# example:
#	is_grub_installed "/dev/sda"
#   echo $?

is_grub_installed()
{
	TMP_DISK=$1
	TMP_FILE=first_sector
    dd if=$TMP_DISK of=$TMP_FILE bs=512 count=1 > /dev/null 2>&1
	GRUB_FLAG_0X3e=` hexdump $TMP_FILE -s 0x3e -n 1 -e '"%02x"' `
	GRUB_FLAG_0X3f=` hexdump $TMP_FILE -s 0x3f -n 1 -e '"%02x"' `
	rm $TMP_FILE -f

	if [ $GRUB_FLAG_0X3e -eq 3 ] && [ $GRUB_FLAG_0X3f -eq 2 ]
	then
		return 1
	fi
	return 0
}

# INPUT: like /dev/sda /dev/sdb
# OUTPUT: return 1 if it is grub2, 0 else
# example:
#	is_grub2_installed "/dev/sda"
#   echo $?

is_grub2_installed()
{
	TMP_DISK=$1
	TMP_FILE=third_sector
    dd if=$TMP_DISK of=$TMP_FILE bs=512 count=1 skip=2 > /dev/null 2>&1
    TMP_FLAG=` hexdump $TMP_FILE -s 0x6 -n 1 -e '"%04x"' `
	rm $TMP_FILE -f

	if [ $TMP_FLAG -eq 4 ]
	then
		return 1
	fi
	return 0
}

# INPUT:
# @DISK: like /dev/sda /dev/sdb

# OUTPUT:
# return /dev/sda1, /dev/sda3,..., return "" if no grub
get_grub_partition()
{
	DISK=$1
	RESULT="0"
	DIR="/tmp/mbr-experiments"
	GRUB_INSTALL_FLAG="0"
	GRUB2_INSTALL_FLAG="0"
	
	rm -rf $DIR
	mkdir -p $DIR
	pushd $DIR > /dev/null 2>&1
	
	get_stage2_dec_address $DISK
	is_grub_installed $DISK
	GRUB_INSTALL_FLAG=`echo $?`
	if [ $GRUB_INSTALL_FLAG -eq 0 ]
	then
		echo "No grub is installed!"
		popd > /dev/null 2>&1
		rm -rf $DIR 
	fi
	
	is_grub2_installed $DISK
	GRUB2_INSTALL_FLAG=`echo $?`
	if [ $GRUB2_INSTALL_FLAG -eq 1 ]
	then
		RESULT="0"
	else 
		if [ $STAGE2_DEC_ADDRESS -eq 1 ] ; then
		    dd if=$DISK of=stage1_5 bs=512 count=2 skip=1 > /dev/null 2>&1
		    RESULT_HEX=` hexdump stage1_5 -s 0x219 -n 1 -e '"%02x"' `
			rm -f stage1_5 
		    RESULT=$(( 0x$RESULT_HEX + 1 ))
		else
		    # use fdisk to decide which partition include the stage2 sectors,
		    # any better method?
		    DISK_PARTITIONS="disk_partions"
		    fdisk -l -u | sed '1,/.*Device Boot.*/d' | sed '/.*Ext*/d' | sed 's/\*/ /' > $DISK_PARTITIONS
		    LINE=`cat $DISK_PARTITIONS | wc -l`
		
		    for i in `seq $LINE`
		    do
				TMP_RESULT=$(cat $DISK_PARTITIONS | awk "NR==$i {print \$1}")
				TMP_START=$(cat $DISK_PARTITIONS | awk "NR==$i {print \$2}")
				TMP_END=$(cat $DISK_PARTITIONS | awk "NR==$i {print \$3}")
			if [ $STAGE2_DEC_ADDRESS -gt $TMP_START ] && [ $STAGE2_DEC_ADDRESS -lt $TMP_END ]
			then
			    RESULT=`echo $TMP_RESULT | sed 's/^[^0-9]*//'`
			    break
			fi
		    done
		fi
	fi
	
	popd > /dev/null 2>&1
	rm -rf $DIR 
	if [ $RESULT -gt 0 ] && [ $RESULT -le 16 ]
	then
		GRUB_PARTITION=$DISK$RESULT
	fi
}

# INPUT:
# @DISK: like /dev/sda /dev/sdb

# OUTPUT:
# return /dev/sda1, /dev/sda3,..., return "" if no grub
get_grub2_partition()
{
	DISK=$1
	RESULT="0"
	DIR="/tmp/mbr-experiments"
	GRUB_INSTALL_FLAG="0"
	GRUB2_INSTALL_FLAG="0"
	
	rm -rf $DIR
	mkdir -p $DIR
	pushd $DIR > /dev/null 2>&1
	
	get_stage2_dec_address $DISK
	is_grub_installed $DISK
	GRUB_INSTALL_FLAG=`echo $?`
	if [ $GRUB_INSTALL_FLAG -eq 0 ]
	then
		echo "No grub is installed!"
		popd > /dev/null 2>&1
		rm -rf $DIR 
	fi
	
	is_grub2_installed $DISK
	GRUB2_INSTALL_FLAG=`echo $?`
	if [ $GRUB2_INSTALL_FLAG -eq 1 ]
	then
		TMP_FILE=second_sector
	    dd if=$DISK of=$TMP_FILE bs=512 count=2 skip=1 > /dev/null 2>&1
	    RESULT_HEX=` hexdump $TMP_FILE -s 0x214 -n 1 -e '"%02x"' `
		rm -f $TMP_FILE
	    RESULT=$(( 0x$RESULT_HEX + 1 ))
	else
		RESULT="0"
	fi

	popd > /dev/null 2>&1
	rm -rf $DIR 
	if [ $RESULT -gt 0 ] && [ $RESULT -le 16 ]
	then
		GRUB_PARTITION=$DISK$RESULT
	fi
}

# global var to show which partition the grub in mbr comes from
GRUB_PARTITION=""
# these are examples to demonstrate how to use funcitons above.
get_grub_partition /dev/sda
echo "$GRUB_PARTITION"

get_grub2_partition /dev/sda
echo "$GRUB_PARTITION"

