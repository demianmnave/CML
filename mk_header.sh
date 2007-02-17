#!/bin/sh
headers=`find cml -name "*.h"`
for file in $headers; do
  echo "... fixing $file.orig -> $file"
  cp $file $file.orig
  ./header.pl < $file.orig > $file
done
