#!/usr/bin/perl

use strict;
use locale;



sub tokenize {
  my ( $text ) = @_;

  my @tokens = split /\s/, $text;
  my $token_len = @tokens;

  return @tokens;
}

my @text = <STDIN>;
my $text_len = @text;
my $indentLevel = 0;
my $lastIndentLevel = 0;

for ( my $i=0; $i < $text_len; $i++ ) {
  my @tokens = tokenize( $text[$i] );

  if ( $tokens[0] =~ /^h(\d)\.$/ ) {
    print "<h$1>"; 
    shift @tokens;
    print join ' ', @tokens;
    print "</h$1>\n";
    next;
  } elsif ( $tokens[0] =~ /^(\*+)$/ ) {
    $indentLevel = length( $1 );
    if ( $indentLevel > $lastIndentLevel ) {
      for ( my $i=0; i<($lastIndentLevel - $indentLevel); i++ ) {
        print "<ul>\n";
      }
    }
    print "<li>"; 
    shift @tokens;
    print join ' ', @tokens;
    print "</li>\n";
    if ( $indentLevel < $lastIndentLevel ) {
      for ( my $i=0; $i<($lastIndentLevel - $indentLevel); $i++ ) {
        print "</ul>\n";
      }
    }

    $lastIndentLevel = $indentLevel;
    next;
  } else {
    if ( $lastIndentLevel > 0 ) {
      print "</ul>\n";
      $lastIndentLevel = 0;
    }
  }

  my $token_len = @tokens;
  if ( $token_len > 0 ) {
    print "<p>";
    print join ' ', @tokens;
    print "</p>\n";
  }
}



