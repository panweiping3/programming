#! /bin/bash

# This script is to show how to use ()
# it mainly is used in arithmetic expressions

x=2
y=8
(( x > 2 ))
echo "result 1:"$?

(( x + y > 2))
echo "result 2:"$?

(( x >= 2 && y < 10))
echo "result 3:"$?

(( y / x ))
echo "result 4:"$?

echo "result 5:"$(( y / x))
a=1 
b=2 
c=3 
(( a = a + 1 )) 
echo $a 
a=$(( a+1, b++, c++)) 
echo $a, $b, $c 

num=10 
total=0
for ((i=0;i<=num;i++))
do
	((total += i))
done

echo $total

echo $(pwd; echo ""; ls .)
