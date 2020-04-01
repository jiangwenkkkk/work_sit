#!/bin/bash


port=2186

#TOPIC_LIST=( 10.128.91.24 10.128.91.25 10.128.91.26 )
TOPIC_LIST=( 10.128.117.19 10.128.117.20 10.128.117.21 )
TOPIC_LIST_COUNT=${#TOPIC_LIST[@]}

for (( i = 0; i < ${TOPIC_LIST_COUNT}; i ++ ))
do
    strMode=`echo srvr | nc ${TOPIC_LIST[i]} $port -w 3 | awk -v mode=${TOPIC_LIST[i]} '$0 ~ /Mode:/ {printf("%s",$0);}'`
    mode=${TOPIC_LIST[i]}
    status=${strMode:6}
    newstr="$mode:$status"
    echo -n "$newstr"
    if [ $i -ne `expr ${TOPIC_LIST_COUNT} - 1` ]; then
        echo -n ";"
    fi
done
