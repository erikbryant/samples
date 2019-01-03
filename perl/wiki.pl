#!/usr/bin/perl

use strict;
use warnings;

use Tokenizer;

my @text = <STDIN>;

my $tokenizer = new Tokenizer( @text );

$tokenizer->setText( @text );
$tokenizer->print();


