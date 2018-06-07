#!/usr/bin/perl

# comments:
# validate address: http://blockchain.info/rawaddr/13VXFcmt6yZyeDTgzbFKGjufWye5qikoji

use strict;
use warnings;

if(!@ARGV){
  die"USAGE: $0 num\n";}

use IO::Prompt;
my $PASS;
if(prompt(-p=>'Passphrase:',-te=>'*')){
  $PASS=$_;}
else{
  die"ERROR: no passphrase\n";}
for(my $i=0;$i<$ARGV[0];$i++){
  print "PA: $PASS::$i\n";
  open(FILE,"|./key -");
  print FILE "$PASS::$i\n";
  close(FILE);}
