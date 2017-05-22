#!/usr/bin/env bash
for (( ; ; ))
do
rm test.txt
java -jar TestGenerate.jar 5 20 >> test.txt
OUT1=$( cat test.txt |  ./test.out )
OUT2=$( cat test.txt | ./valid.out )
if [ "$OUT1" != "$OUT2" ]; then
   exit
fi
done

