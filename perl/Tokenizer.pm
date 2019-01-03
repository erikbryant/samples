package Tokenizer;

use warnings;
use strict;

sub new {
  my $class = shift;

  my $self = {
    _text => undef
  };

  bless $self, 'Tokenizer';

  return $self;
}

sub setText {
  my ($self) = @_;
  my (@text) = @{shift};

  my $element;

  foreach $element (@text) {
    print $element . "\n";
  }

  $self->{_text} = "this is a test";
}

sub print {
  my ( $self ) = @_;

  print $self->{_text} . "\n";
}


1
