#! /bin/sh

function ip2num()
{
    IP_ADDRESS_NUMBER=0
    IP=$1
    a=`echo $IP | awk -F'.' '{print $1}'`
    b=`echo $IP | awk -F'.' '{print $2}'`
    c=`echo $IP | awk -F'.' '{print $3}'`
    d=`echo $IP | awk -F'.' '{print $4}'`
    
	#(( IP_ADDRESS_NUMBER=($a<<24)+($b<<16)+($c<<8)+$d ))
    	(( IP_ADDRESS_NUMBER=($d<<24)+($c<<16)+($b<<8)+$a ))

    return 0
}

ip2num $1
echo "IP_ADDRESS_NUMBER="$IP_ADDRESS_NUMBER
printf "%x\n" "$IP_ADDRESS_NUMBER"
