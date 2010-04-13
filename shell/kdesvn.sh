#! /bin/sh

if [ $# > 1 ]
then
    for dir in $@
    do
        cd $dir
        svn cleanup
        svn up
        echo "svn "$dir "successfully !"
        cd ..
    done
fi
