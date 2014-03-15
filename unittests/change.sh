#!/bin/bash

for file in ${*}; do
  sed 's/bold::Test/pat::Test/' ${file} > ${file}.bak
  mv ${file}.bak ${file}
done
