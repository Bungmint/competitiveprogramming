#!/bin/zsh
# Generates contest folder with a set number of problems
# How to use - "generate.sh CONTEST_NAME NUMBER_OF_PROBLEMS"
# Don't Forget to chmod if needed!

### VARIABLES ###

CONTEST=$1
NUM=$2
cnt=0
COPY_FROM="../templates/miscellaneous/template.cpp"

### MAIN ###

mkdir $CONTEST
cd $CONTEST
for i in {A..Z}; do
    if [[ $cnt -eq $NUM ]]; then
        break
    fi
    true $((cnt++))
    cp $COPY_FROM "$i.cpp"
    code --goto "$i.cpp":68:4
    sleep .1
done
echo "$CONTEST folder is ready to go!"
