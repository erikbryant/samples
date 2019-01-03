#!/usr/bin/perl

#
# Given a batch of photos, make a slideshow.
#  step 1: create thumbnails
#  step 2: create a 'show.def' file
#

if ( $#ARGV < 0 )
{
    die "Insufficient arguments.\nUsage: makeshow <file1> [<file2>...]\n";
}

$outwidth = 300;
$hires    = "";
$archive  = "";

print "Enter a title: ";
$title = <STDIN>;
chop $title;

print "Enter an intro: ";
$intro = <STDIN>;
chop $intro;

print "Archive file: [none] ";
$archive = <STDIN>;
chop $archive;

print "Delay: [5] ";
$delay = <STDIN>;
chop $delay;
if ( $delay eq "" ) { $delay = "5"; }

$hires = "";
print "Image width: [original] ";
$outwidth = <STDIN>;
chop $outwidth;
if ( $outwidth ne "" )
{
    print "Hi-res prefix: [nohires] ";
    $hires = <STDIN>;
    chop $hires;
}

#
# Create thumbnails.
#
if ( $outwidth ne "" )
{
    $prefix = $hires;
    if ( $prefix eq "" )
    {
	$prefix = "__DELPREFIX__";
    }
    system "/var/www/cgi-bin/thumb.pl $outwidth $prefix @ARGV";
}

#
# Create the 'show.def' file.
#
open ( FILE, ">show.def" ) || die "Could not open show.def.";

# Write out the settings.
if ( $title ne "" ) { print FILE "title\n$title\n\n"; }
if ( $hires ne "" ) { print FILE "hires\n$hires\n\n"; }
if ( $intro ne "" ) { print FILE "intro\n$intro\n\n"; }
if ( $archive ne "" ) { print FILE "archive\n$archive\n\n"; }
if ( $delay ne "" ) { print FILE "delay\n$delay\n\n"; }

# Write out each image name and a placeholder for its caption.
foreach $image_file ( @ARGV )
{
    print FILE "$image_file\n";
    print FILE "<!--><!-->\n\n";
}

close ( FILE );
