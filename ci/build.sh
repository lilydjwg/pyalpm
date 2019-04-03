#!/bin/bash

branch=$(git rev-parse --abbrev-ref HEAD)
tmpdir=/tmp/pacman

python3 -m py_compile $(git ls-files '*.py')
sudo mkdir /var/cache/pacman/pkg

if [ "$branch" == "next" ]; then
  echo "Building with pacman-git"
  ./build-pacman-git.sh $tmpdir
else
  CC=gcc make build
fi

LD_LIBRARY_PATH=$tmpdir/usr/include make test
make pylint
make -C doc html
