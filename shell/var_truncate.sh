#! /bin/sh

VAR=abcdefg
echo ${VAR##*d} 

#???????????????//
VAR=abcdefg
echo ${VAR%%*a} 
