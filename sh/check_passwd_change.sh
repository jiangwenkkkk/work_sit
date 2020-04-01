#!/usr/bin/env bash

function get_passwd_change()
{
    for ip in $1
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

get_passwd_change ip_list.txt > db.txt
sed -ne '/\([0-9]\+%\)/p'  -ne '/^[0-9]\+/p' db.txt | awk '{if(match($1,"95")){printf $1"\n"} else {printf $1": \t" $5 ; len = length($5); subs = substr($5,1, len-1); num = strtonum(subs); if (num > 1) {printf "---no"}printf "\n"}}' ;

