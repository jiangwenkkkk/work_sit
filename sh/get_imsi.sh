#!/usr/bin/env bash

function get_imsitime()
{
    for ip in `cat $1`
do
    echo $ip

    /usr/bin/expect <<- EOF

    spawn ssh james@$ip -p 29367
expect {
"*password:" { send "james@home\r" }
}
expect "*$"
send "ll ~\r"

expect "*$ "
send "exit\r"

EOF
done

}

get_imsitime ip_list.txt
sed -n '/[10.142.234.,imsibak]/p' hell.txt;
