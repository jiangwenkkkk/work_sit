#!/usr/bin/env bash


/usr/bin/expect <<- EOF

set timeout 100;


spawn scp -p 5151 -r bin js_app@10.28.117.34


expect {
 "*password:" { send "jsapp@12\n";}
}

EOF




