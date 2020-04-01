##!/usr/bin/env bash
#
#line_count=0
#file_num=0
#bill_count=0
#n=0
#while [ $n -le 580000 ]
#do
#    mv L*  ../tmp/
#sleep 1
#
#    file_num=`ls  ../tmp/L* |wc -l`
#    line_count=`wc -l ../tmp/L* |grep total|awk '{print $1}'`
#    bill_count=$(($bill_count+$line_count-2*$file_num))
#    echo $bill_count"\n" >> bill_cout.txt
#    rm ../tmp/L*
#    sleep 80
#    let n++    #或者写作n=$(( $n + 1 ))
#done
#
#echo $bill_count >> bill_cout.txt


#!/usr/bin/env bash

line_count=0
file_num=0
bill_count=0
n=0
all_file_num=0
while [ $n -le 580000 ]
do
    mv L*  ../tmp/
    sleep 1

    file_num=`ls  ../tmp/L* |wc -l`
    all_file_num=$(($file_num+$all_file_num))
    line_count=`wc -l ../tmp/L* |grep total|awk '{print $1}'`
    bill_count=$(($bill_count+$line_count-2*$file_num))
    echo "allfilenum: " $all_file_num >> bill_count.txt
    echo "allbill:" $bill_count >> bill_count.txt

    rm ../tmp/L*
    sleep 80
    let n++    #或者写作n=$(( $n + 1 ))
done

echo $allfilenum" "$bill_count >> bill_count.txt