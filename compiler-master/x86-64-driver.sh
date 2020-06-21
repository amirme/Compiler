#!/bin/bash

FILENAME="$1"
PROLOGUE="lexyacc-code_lab3/Prologue.s"
EPILOGUE="lexyacc-code_lab3/Epilogue.s"
CALC3I="bin/calc3i.exe"

USAGE(){
  echo "HOW TO RUN: ./x86-64-driver.sh <FILENAME.calc>"
  echo "EXAMPLE: ./x86-64-driver.sh calc/fact.calc"
  echo "after succesful execution FILENAME.s and FILENAME will be created in the root directory..."
}

#get the name of the file without path or extension
FILE="$(basename -- $FILENAME)"
EXTENSION="${FILE##*.}"
BASEFILENAME="${FILE%.*}"

SOURCEFILE="src/fact.s"

#check to see if the user passed the name of a .calc file
if [[ $# != 1 ]]; then
    echo "Please pass the name of a .calc file as an argument...!"
    USAGE
    exit 1
fi

#check to see if it is a .calc file
if [[ ${FILENAME: -5} != ".calc" ]]; then
    echo "Not a valid .calc file...!"
		USAGE
		exit 1
fi

#check to see if the file exist
if [[ ! -f ${FILENAME} ]]; then
    echo "${FILENAME} file not found...!"
    USAGE
    exit 1
fi



#creating .s and executable file using prologue, main code and epilogue
cat $PROLOGUE > $BASEFILENAME.s
$CALC3I < $FILENAME >> $BASEFILENAME.s
cat $EPILOGUE >> $BASEFILENAME.s
if [[ "$BASEFILENAME" == "fact" ]]; then
  gcc $BASEFILENAME.s $SOURCEFILE -o $BASEFILENAME
else
  gcc $BASEFILENAME.s -o $BASEFILENAME
fi
