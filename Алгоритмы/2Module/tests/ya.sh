#!/usr/bin/env bash
calcSize(){
    ls -laR $1 | awk '{ sum+=$5 }END{print sum}'
}

echo $( calcSize '/home/' )
