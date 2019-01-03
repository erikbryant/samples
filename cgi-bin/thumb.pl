#!/usr/bin/perl

#
# A script to read in a selection of images and to
# create thumbnail versions of each.
#

#
# At some point it would be good to allow the user
# to specify a maximum width/height for the image
# and only images that exceed that will be processed.
# Of course, that brings of the issue of how to tell
# the script which do and don't have hi-res versions
# (perhaps allow the hi-res name on the image line
# right after the low-res name or allow it right
# after the credit line).
#

if ( $#ARGV < 2 )
{
    die "Insufficient arguments.\nUsage: thumb <width> <prefix> <file1> [<file2>...]\n";
}

$outwidth = shift @ARGV;
$prefix   = shift @ARGV;
#$mogrify  = "/home/ebryant/public_html/ebCGI/imagemagick/bin/mogrify";
$mogrify  = "mogrify";
$temp = "xxtempfilexx";

foreach $image_file ( @ARGV )
{
  # Increase the compression on the original file
  system "mv $image_file $temp";
  system "$mogrify -quality 75 $temp";
  system "mv $temp.mgk $image_file";
  system "rm -f $temp";

  # There's garbage in these images...convert to another image
  # format and back to remove it. Yes, this is a hack.
  system "mv $image_file $temp";
  system "$mogrify -format gif $temp";
  system "$mogrify -format jpg $temp.gif";
  system "rm $temp $temp.gif";
  system "mv $temp.jpg $image_file";

  if ( $prefix ne "__DELPREFIX__" )
  {
    $hires_file = "$prefix" . $image_file;
    system "cp $image_file $hires_file";
  }

  # Create a smaller version of the original file
  system "mv $image_file $temp";
  system "$mogrify -geometry $outwidth $temp";
  system "mv $temp.mgk $image_file";
  system "rm -f $temp";
}
