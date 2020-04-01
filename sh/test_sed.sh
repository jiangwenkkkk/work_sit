#!/usr/bin/env bash


#echo 10.142.234.11 > hell.txt
#echo ayes >> hell.txt
#echo hllo >> hell.txt
# sed  -ne '/imsibak/p'  hell.txt;-ne '/imsibak/p'


#
#file=`date '+%Y%m%d'`.imsibak
#file=20181113.imsibak
#sed -ne "s/.*@\(10.142.234.[0-9]\+\)'[^0-9]*/\1/p" -ne 's/.* \([0-9]\+.imsibak\).*/\1/p' imsi.txt |
#awk 'BEGIN{count = 0}{if(NR%2==0){printf $0"---";  if( $0 != "'$file'" ){printf " no"} else{printf " ok"} printf "\n"; count += 1}else{printf "%s: ",$0}} END{printf "all:" count}';
#
#
#


#sed -ne '/\([0-9]\+%\)/p'  -ne '/^[0-9]\+/p' db.txt | awk '{if(match($1, "95.169.15.105")) printf $1}' ;
#sed -ne '/\([0-9]\+%\)/p'  -ne '/^[0-9]\+/p' db.txt | awk '{if(match($1,"95")){printf $1"\n"} else {printf $1": \t" $5 ; len = length($5); subs = substr($5,1, len-1); num = strtonum(subs); if (num > 1) {printf "---no"}printf "\n"}}' ;
#sed   -ne '/^[0-9]\+/p' db.txt;
#sed   -ne '/^[0-9]\+/p' db.txt;

#sed -ne '/\([0-9]\+%\)/p'  -ne '/^[0-9]\+/p' db.txt | awk -f db.awk
#sed   -ne 's/*\([0-9]\+\)*/p' db.txt
#
#ps -ef | grep java | grep  QuorumPeerMain|grep "/app/kafka/config/zookeeper.properties"| sed -ne "s/.*\/\(app\/kafka\/config\/zookeeper.properties\)[^0-9]*/\1/p"


#sed -e 's/this/a/; s/T/aaa/' log.txt
#

#sed -e 's/[tT]/aaa/g; s/T/aaa/g' log.txt
#sed -e '/3/, /5/d'  log.txt
#sed  -n  '/aa/p' log.txt
sed  -n  '/aa/p' log.txt