#!/usr/bin/perl

# /etc/xinetd.d/echo-stream
#
use strict;
use Socket;
use IO::Handle;
my ($byte_out,$byte_in) = (0,0);
my $host = shift || 'localhost';
my $port = shift || getservbyname('echo','tcp');
my $protocol = getprotobyname('tcp');
$host = inet_aton($host) or die "$host:unknown host";


socket(SOCK,AF_INET,SOCK_STREAM,$protocol)
        or die "socket() failed:$!";
my $dest_addr = sockaddr_in($port,$host);
connect(SOCK,$dest_addr) or die "connect() failed:$!";


SOCK->autoflush(1);


while(my $msg_out = <>){
        print SOCK $msg_out;
        my $msg_in = <SOCK>;
        print $msg_in;


        $byte_out += length($msg_out);
        $byte_in += length($msg_in);
}


close SOCK;
print "byte_sent = $byte_out,byte_received = $byte_in\n";
