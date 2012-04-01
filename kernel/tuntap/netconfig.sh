#!/bin/sh

ifconfig tun0 0.0.0.0 up
route add 10.10.10.2 dev tun0
