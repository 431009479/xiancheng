#!/bin/bash
TIME=$(date "+%Y-%m-%d__%H:%M:%S")



eval `df -T -m -x tmpfs -x devtmpfs | tail -n +2|\
    awk -v DiskSum=0 -v DiskLeft=0\
        '{printf("Pname["NR"]=%s;Psum["NR"]=%d;Pleft["NR"]=%d;Puseperc["NR"]=%s;",$7,$3,$4,$6); DiskSum+=$3; DiskLeft+=$5}\
        END {printf("Pnum=%d;DiskSum=%d;DiskLeft=%d;", NR, DiskSum, DiskLeft)}'`

for(( i = 1; i <= ${Pnum}; i++ ));do
    echo "$TIME 1 ${Pname[$i]} ${Psum[$i]} ${pleft[$i]} ${Puseperc[$i]}"
done

DiskPerc=$[ (100 - ${DiskLeft} * 100/${DiskSum}) ]
echo "$TIME 0 disk $diskSum $DiskLeft $DiskPerc%"
