#!/bin/bash
DIRECTORY=dataset
if [ ! -d ${DIRECTORY} ]; then
 mkdir ${DIRECTORY}
fi

for f in `seq 1 70`
do
echo ${f}
./gen >> ${DIRECTORY}/${f}.tst
done

for f in `seq 71 80`
do
echo ${f}
 ./gen -m >> ${DIRECTORY}/${f}.tst
done

for f in `seq 81 85`
do
echo ${f}
 ./gen -e >> ${DIRECTORY}/${f}.tst
done

for f in `seq 86 90`
do
echo ${f}
 ./gen -enr >> ${DIRECTORY}/${f}.tst
done

for f in `seq 91 95`
do
echo ${f}
 ./gen -em >> ${DIRECTORY}/${f}.tst
done

for f in `seq 96 100`
do
echo ${f}
 ./gen -enrm >> ${DIRECTORY}/${f}.tst
done

./gen -Em >> ${DIRECTORY}/121.tst
