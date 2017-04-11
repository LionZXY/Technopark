#!/usr/bin/env bash
FILE=benchmark_result.csv
FILES_TEST=./dataset/*.tst
PROGRAMS=./programm/*

if [ -d ${FILE} ]; then
 rm ${FILE}
fi

FILES_TEST=$(sort <<<"${FILES_TEST[*]}" )
PROGRAMS=$(sort <<<"${PROGRAMS[*]}" )

( IFS=$'\t'; echo "Номер таска$IFS${PROGRAMS[*]}" ) >> ${FILE}

for f in $FILES_TEST
do
    RESULTS=()
    filename=$(basename "$f")
    filename="${filename%.*}"
    for pr in $PROGRAMS
    do
        timeBench=$( { time cat ${f} | ${pr}; } 2>&1 | grep real )
        timeBench="${timeBench##*0m}"
        timeBench="${timeBench%s*}"
        RESULTS+=${timeBench}
    done
    ( IFS=$'\t'; echo "$filename$IFS${RESULTS[*]}" ) >> ${FILE}
done