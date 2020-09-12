#!/bin/bash

while [ 1 ]
    do
        Cnt1=`ps -aux|grep "seekware-tcpip"|grep -v grep|wc -l`

        Cnt2=`ps -aux|grep "seekware-stream"|grep -v grep|wc -l`

        PROCESS1=`ps -aux|grep "seekware-tcpip"|grep -v grep|awk '{print $1}'`

        PROCESS2=`ps -aux|grep "seekware-stream"|grep -v grep|awk '{print $1}'`

    if [ $Cnt1 -ne 0 ]
        then
            echo "seekware-tcpip (PID : $PROCESS1) alredy runing"
    else
        seekware-tcpip &
        echo "seekware-tcpip run"
    fi

    if [ $Cnt2 -ne 0 ]
        then
            echo "seekware-stream (PID : $PROCESS2) alredy runing"
    else
        seekware-stream &
        echo "seekware-stream run"
    fi

    sleep 3
done

