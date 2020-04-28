#!/bin/bash

if [[ $# -lt 1 ]];then
    echo "Usage:$0 Dyaver"
fi

#时间
TIME=$(date "+%Y-%m-%d__%H:%M:%S")
DyAver=$1

MemValues=(`free -m |head -2 | tail -1 |awk '{printf"%s %s",$2, $3}'`)

MemUsedPrec=`echo "scale=1; ${MemValues[1]} * 100/${MemValues[0]}" | bc`

NowAver=`echo "scale=1; 0.7*${MemUsedPrec} + 0.3 * ${DyAver}" | bc`

Used=`echo "${MemValues[0]} - ${MemValues[1]}" | bc`

echo "$TIME ${MemValues[0]}M ${Used}M $MemUsedPrec% $NowAver%"
