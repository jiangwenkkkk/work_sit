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
expect "*$ "
send "df \r"

expect "*$ "
send "exit\r"

EOF
    done

}

get_imsitime ip_list.txt > db.txt
sed -ne "s/.*@\(10.142.234.[0-9]\+\)'[^0-9]*/\1/p"  -ne '/^[0-9]\+/p' db.txt | awk -f db.awk

##!/usr/bin/env bash
#
#function get_disk_info()
#{
#    for ip in `cat $1`
#    do
#        echo $ip
#
#        /usr/bin/expect <<- EOF
#
#    spawn ssh roam@$ip
#expect {
#"*password:" { send "roam\r" }
#}
#expect "*$ "
#send "df \r"
#
#expect "*$ "
#send "exit\r"
#
#EOF
#    done
#
#}
#
#get_imsitime ip_list.txt > db.txt
#sed -ne "s/.*@\(10.142.234.[0-9]\+\)'[^0-9]*/\1/p"  -ne '/^[0-9]\+/p' db.txt | awk -f db.awk
