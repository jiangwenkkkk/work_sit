#!/usr/bin/env bash

#debug test
test=1

if [ $test == 1 ]
then
    local_ip=192.168.0.102

    path=`pwd`
    ip_file=$path/ip_list.txt
    local_path=/Users/james/jameswork/james/find_use/test/jameswork/tmp
    user=james
    password=james@home
    file=path
else
    local_ip=`ifconfig | grep -E "10\.142\.234\." | awk '{print $2}'`
    path=`pwd`
    ip_file=$path/ip_list.txt
    local_path=$path
    user=roam
    password=roam
fi



for server_ip in `cat $ip_file`
do
    if [ $server_ip == $local_ip ]
    then
        continue
    fi

    /usr/bin/expect <<- EOF
    spawn ssh $user@$server_ip -p 29367

expect {
"password:" { send "$password\r" }
}
expect -re "$ "

send "ll /home/james | sed '2p' ;\r "

expect -re "$ "
send "exit\r"
expect "logout"

EOF

done

sed -i '/^\t/!d' asdqwe.txt;
sed -i -r 's/^(\t)(.)/\2/g' asdqwe.txt;

#df -h | sed '1d;s/%//g' | awk 'BEGIN{OFS="\t";}{if [ $9 != `date){print "      "x,$1,$2,$3,$4,$5"%",$6};}' x=`ifconfig | grep -E "10\.142\.234\." | awk '{print $2}'`;
#ll /app/roam/dbinfo | sed '' | awk 'BEGIN{OFS="\t";}{if($9 != strdate ) {print "      "x,$1,$2,$3,$4,$5"%",$6};}' x=`ifconfig | grep -E "10\.142\.234\." | awk '{print $2}'` strdate=`date '+%Y%m%d'`;
#
#ll /app/roam/dbinfo | sed '2p' | awk '{if ( $9 != datestr ) print  datestr; print $9}' datestr=`date '+%Y%m%d'`.imsibak;
#ll /app/roam/dbinfo | sed '2p' | awk '{if ( $9 == datestr )  print $9}' datestr=`date '+%Y%m%d'`.imsibak;
#ll /app/roam/dbinfo | sed '2p' | awk '{if ( $9 != datestr )  print $9}' datestr=`date '+%Y%m%d'`.imsibak;
#ll /app/roam/dbinfo | sed '2p' | awk '{  print $9}' datestr=`date '+%Y%m%d'`.imsibak;
#
#ll /app/roam/dbinfo | sed '2p' | awk '{ print aip, $9 }'  aip=`ifconfig | grep -E "10\.142\.234\." | awk '{print $2}'`;

#| awk '{if ( $9 == datestr )  print ip, $9 }' datestr=`date '+%Y%m%d'`.imsibak ip=`ifconfig | grep -E "10\.142\.234\." | awk '{print $2}'`

function get_imsitime()
{
    for ip in `cat $1`
    do
        echo useinfo $ip
        /usr/bin/expect <<-EOF

set timeout 100;

spawn ssh roam@10.142.234.$ip

expect {
 "*yes/no" { send "yes\n"; exp_continue}
 "*password:" { send "roam\n";}
}

expect "*$ "
send "echo useinfo `ll /app/roam/dbinfo | sed '2p'`;\r"

expect "*$ "
send "exit\n"

EOF

    done

}

get_imsitime ip_list.txt > imsi.txt
sed -i '/'
