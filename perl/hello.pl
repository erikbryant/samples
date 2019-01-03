#!/usr/bin/perl

use strict;

use Getopt::Long;

my $PI = 3.14159;

sub area {
  my ( $radius ) = @_;

  return ( $radius * $radius * $PI );
}

my $verbose = 0;
my $name    = "";
my $result  = 0;
my $arg     = "";
my $i       = 0;
my $r       = 0;
my $a       = 0;

$result = GetOptions(
  "verbose=i" => \$verbose,
  "name=s"    => \$name
);

if ( $result == 1 ) {
  print "Verbose level = $verbose\n";
  print "Name          = $name\n";
} else {
  print "Result        = $result\n";
  die;
}

print "Hello, world!\n";

foreach $arg (@ARGV) {
  print "ARGV[$i]: $arg\n";
  $i++;
}

$r = 10.2;
$a = area( $r );
print "The area of a circle with radius: $r is: $a\n";

exit

