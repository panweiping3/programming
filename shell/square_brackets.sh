#! /bin/bash

# This script is to show how to use []

NAME=pwp
ADDRESS=beijing

# no quote is ok
test $NAME = pwp
echo "test result 1:"$?

test $NAME = "pwp"
echo "test result 2:"$?

# test does not support wildcard 
test $NAME = "p?p"
echo "test result 3:"$?

# -a means and
# -o means or
test $NAME = "pwp" -a $ADDRESS = "beijing"
echo "test result 4:"$?

# no quote is ok
[ $NAME = pwp ]
echo "test result 5:"$?

[ $NAME = "pwp" ]
echo "test result 6:"$?

# test does not support wildcard 
[ $NAME = "p?p" ]
echo "test result 7:"$?

[ $NAME = "pwp" -a $ADDRESS = "beijing" ]
echo "test result 8:"$?

# test and [] can test arithmetic expression
# but not intuitive
[ 3 -gt 2 ]
echo "test result 9:"$?

[ 3 > 2 ]
echo "test result 10:"$?

[ 3 > 5 -a 9 > 8 ]
echo "test result 11:"$?

[ 3 > 5 ] && [ 9 > 8 ]
echo "test result 12:"$?

# [[ ]] support wildcard
[[ $NAME = p?p ]]
echo "test result 13:"$?

# 算术扩展
x=$[(5 + 8) / 4 ]
echo "test result 14:"$x

#wildcard
[[ $NAME = [a-z]wp ]]
echo "test result 15:"$?

