#!/bin/bash

#Description: 根据配置对指定表进行添加分区操作


#Author:root
#Version:1.0
#CreateTime:2019-01-22 09:18:19




base_dir=$(cd `dirname $0` pwd)
dt=$(date "+%Y%m%d%H%M%S")




#根据实际情况设定hiveurl
hive_url="jdbc:hive2://dcdn001:2181,dcdn002:2181,dckdc2:2181,dcnn1:2181,dcnn2:2181/ serviceDiscoveryMode=zooKeeper zooKeeperNamespace=hiveserver2"
#设置hive用户
hive_user="hive"


#添加的账期
v_dates="$(date -d  "+1 days" "+%Y%m%d") $(date -d  "+2 days" "+%Y%m%d")"


#添加的所有省分 provinceid
provinces="10 22 21 23 351 311 791 531 371 471 451 24 27 431 731 20 25 771 898 28 571 851 551 871 591 29 891 931 971 951 991"
#添加的表
tables="tb1 tb2"


if [ ! -d $base_dir/sql ]; then
    mkdir $base_dir/sql
fi


script_file=$base_dir/sql/add_part_${dt}.sql


for v_date in ${v_dates}
do
    for table in ${tables}
    do
        for provinceid in ${provinces}
        do
            echo "$v_date $table $provinceid"
            echo "ALTER TABLE ${table} ADD PARTITION (date_no='${v_date}',provinceid='${provinceid}');" >> $script_file
        done
    done
done


cmd="beeline -u \"$hive_url\" -n ${hive_user} -f $script_file"
echo $cmd
exec $cmd
