#!/bin/zsh
# Generates contest folder with set number of problems
# How to use - "generate.sh CONTEST_NAME NUMBER_OF_PROBLEMS INCLUDE_CONTEST_NAME"
# Don't Forget to chmod if needed!

### VARIABLES ###

CONTEST=$1
NUM=$2
ONLY_LETTERS=$3
cnt=0
COPY_FROM="../templates/template.cpp"

### MAIN ###

mkdir $CONTEST
cd $CONTEST
for i in {A..Z}; do
    if [[ $cnt -eq $NUM ]]; then
        break
    fi
    true $((cnt++))
    if [ $ONLY_LETTERS = "0" ]; then
        cp $COPY_FROM "$i.cpp"
    else
        cp $COPY_FROM "${CONTEST}$i.cpp"
    fi
done
echo "$CONTEST folder is ready to go!"
