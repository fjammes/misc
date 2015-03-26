#!/usr/bin/perl
use POSIX qw(mkfifo);

$fn = "/tmp/ssiclfifo" if !($fn = $ARGV[0]);

mkfifo($fn, 0700);
open(FIFO, $fn)   or die "ssiclwin: Unable to open fifi $fn; $!";

while($line = <FIFO>) {print $line;}
