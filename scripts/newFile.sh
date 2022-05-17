#!/bin/zsh
# Generates a new file in a designated folder with the template file loaded up

### VARIABLES ###

NAME=$1
COPY_FROM="templates/template.cpp"
COPY_TO="currentTask"

### MAIN ###

if [ -z $NAME ]; then
    cp $COPY_FROM "$COPY_TO/A.cpp"
    code "$COPY_TO/A.cpp"
else
    cp $COPY_FROM "$COPY_TO/$NAME.cpp"
    code "$COPY_TO/$NAME.cpp"
fi
echo "Your file has been successfully generated!"
