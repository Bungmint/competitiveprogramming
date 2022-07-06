#!/bin/zsh
# Generates a new file in a designated folder with the template file loaded up

### VARIABLES ###

NAME=$1
COPY_FROM="templates/template.cpp"
COPY_TO="currentTask"

### MAIN ###

if [ -z $NAME ]; then
    NAME=A
    cp $COPY_FROM "$COPY_TO/A.cpp"
    code "$COPY_TO/A.cpp"
fi
cp $COPY_FROM "$COPY_TO/$NAME.cpp"
code --goto "$COPY_TO/$NAME.cpp":62:4

echo "Your file has been successfully generated!"
