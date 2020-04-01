#!/usr/bin/env bash

path=`pwd`
ip_file=$path/ip_list.txt

local_ip=`ifconfig | grep -E "10\.142\.234\." | awk '{print $2}'`

file=$path/

for server_ip in `cat $ip_file`
do
    if [ $server_ip == $local_ip ]
    then
        continue
    fi

    file=$path/info_${server_ip}.log
    expect -c "
           spawn scp $user@$server_ip:$file $local_path
           expect {
               yes/no { send \"yes\r\"; exp_continue }
               *assword* { send \"${password}\r\" }
           };
           expect 100%
           expect eof ;
       "
done
