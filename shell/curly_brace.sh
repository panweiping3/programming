#! /bin/bash

# This script is to show how to use {}

echo pwp{111,222}

NAME=pwp
echo "1:"$NAME
echo "2:"$NAMEsdfa
echo "3:"$NAME"sdfa"
echo "4:"${NAME}sdfa

newvar=""
echo "5:"${newvar:-def}

# newvar is still empty
echo "6:"$newvar
newvar=abc
echo "7:"${newvar:-def}
echo "8:"$newvar


newvar=
echo "9:"${newvar:=def}
# newvar is def
echo "10:"$newvar

newvar=abc
echo "11:"${newvar:=def}
# newvar is not changed
echo "12:"$newvar


newvar=
#show empty
echo "13:"${newvar:+def}
# newvar is still empty
echo "14:"$newvar

newvar=abc
#show def
echo "15:"${newvar:+def}
# newvar is not changed
echo "16:"$newvar


newvar=a 
echo "19:"${newvar:?没有设置newvar的值} 
echo "20:"$newvar
newvar= 
# quit immediately
#echo "17:"${newvar:?没有设置newvar的值} 

NAME=abc_pwp_def
# pattern not find
echo "21:"${NAME%pwp}
echo "22:"$NAME

NAME=abc_pwp_def
# pattern find
# 最小匹配
echo "23:"${NAME%p*f}
echo "24:"$NAME

NAME=abc_pwp_def
echo "25:"${NAME%%pwp}
echo "26:"$NAME

NAME=abc_pwp_def
# 最长匹配
echo "27:"${NAME%%p*f}
echo "28:"$NAME

NAME=abc_pwp_def
echo "29:"${NAME#pwp}
echo "30:"$NAME

NAME=abc_pwp_def
# 最小匹配
echo "31:"${NAME#p*f}
echo "32:"$NAME

NAME=abc_pwp_def
echo "31:"${NAME#a*p}
echo "32:"$NAME

NAME=abc_pwp_def
echo "33:"${NAME##pwp}
echo "34:"$NAME

NAME=abc_pwp_def
# 最小匹配
echo "35:"${NAME##p*f}
echo "36:"$NAME

NAME=abc_pwp_def
echo "37:"${NAME##a*p}
echo "38:"$NAME

NAME=abc_pwp_def
echo "39:"${#NAME}
