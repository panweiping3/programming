#! /bin/sh
yum -y install git make gcc xmlto asciidoc hmaccalc bzip2

rm -rf rhel6 
git clone git://git.engineering.redhat.com/users/arozansk/rhel6.git
mkdir rhel6_build
cp /boot/config* rhel6_build/.config

cd rhel6
make O=../rhel6_build/ oldconfig

P=`cat /proc/cpuinfo  |grep processor |wc -l`
((P=$P + $P))

make O=../rhel6_build/ all -j $P
make O=../rhel6_build/ modules_install
make O=../rhel6_build/ install

echo "rhel6 is ready"
echo "please modify grub.conf"
