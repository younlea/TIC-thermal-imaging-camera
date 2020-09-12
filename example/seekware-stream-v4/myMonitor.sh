#!/bin/bash

while [ 1 ]
    do
        Cnt=`ps -ex|grep "seekware-tcpip"|grep -v grep|wc -l`
        PROCESS=`ps -ex|grep "seekware-tcpip"|grep -v grep|awk '{print $1}'`
    if [ $Cnt -ne 0 ]
        then
            echo "seekware-tcpip (PID : $PROCESS) alredy runing"
    else
        seekware-tcpip &
        echo "seekware-tcpip run"
fi
    sleep 3
done

