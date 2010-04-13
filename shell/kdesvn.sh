#! /bin/sh

if [ "$#" -gt "0" ]
then
    for dir in $@
    do
        cd $dir
        svn cleanup
        svn up
        echo "svn "$dir "successfully !"
        cd ..
    done
else
for dir in kdesupport kdelibs kdebase kdeartwork kdegraphics kdeplasma-addons 
do
    cd $dir
    svn cleanup
    svn up
    echo "svn "$dir "successfully !"
    cd ..
done
fi

