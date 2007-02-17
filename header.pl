#!/usr/bin/env perl
use strict;
my $copyright = "
Copyright (c) 2007 Jesse Anders and Demian Nave http://cmldev.net/

The Configurable Math Library (CML) is distributed under the terms of the
Boost Software License, v1.0 (see cml/LICENSE for details).
";

while (<>) {
  if(/\@\@COPYRIGHT\@\@/) {
    my $replace = $_;
    $replace =~ s/\@\@COPYRIGHT\@\@/$copyright/;
    print $replace;
  } else {
    print $_;
  }
  #s/"\@\@COPYRIGHT\@\@"/$copyright/g;
  #print $_;
}
