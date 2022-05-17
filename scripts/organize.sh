#!/bin/zsh
# Puts files with the same contest name in the same folder

prefix="./"
add="ARC"


cd atcoder

for fileName in ./$add*.*; do
    withoutF=${fileName%.*}
    z=${withoutF#$prefix${add}}
    alp=${z##*([0-9])}
    z=${z%[[:alpha:]]}
    dirName="${add}${z}"
    echo $z $alp $dirName
    if [ ! -d $dirName ]; then
        mkdir $dirName
    fi
    mv $fileName $dirName/$alp.cpp
done;