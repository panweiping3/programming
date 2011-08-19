#!/usr/bin/expect
spawn kinit wpan
expect "Password for wpan@REDHAT.COM:" 
send "PANWEIPING3\@163\.com\r" 
expect eof
