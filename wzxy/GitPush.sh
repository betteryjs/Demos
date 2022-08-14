#! /usr/bin/sh

echo "init PUSH"

git add .
git commit -m $1
git push -f github master
git push -f tencent master
git push -f gitlab master



