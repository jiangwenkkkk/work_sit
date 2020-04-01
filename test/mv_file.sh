#!/usr/bin/ bash
source bash_
while 2>1
do
    mv LNIG_*025.*.*   /jsdata/vnode/sr/roam_in/025
    mv LNIG_*022.*.*   /jsdata/vnode/sr/roam_in/022
    mv LNIG_*021.*.*   /jsdata/vnode/sr/roam_in/021
    mv LNIG_*023.*.*   /jsdata/vnode/sr/roam_in/023
    mv LNIG_*311.*.*   /jsdata/vnode/sr/roam_in/311
    mv LNIG_*351.*.*   /jsdata/vnode/sr/roam_in/351
    mv LNIG_*471.*.*   /jsdata/vnode/sr/roam_in/471
    mv LNIG_*024.*.*   /jsdata/vnode/sr/roam_in/024
    mv LNIG_*451.*.*   /jsdata/vnode/sr/roam_in/451
    mv LNIG_*431.*.*   /jsdata/vnode/sr/roam_in/431
    mv LNIG_*971.*.*   /jsdata/vnode/sr/roam_in/971
    mv LNIG_*028.*.*   /jsdata/vnode/sr/roam_in/028
    mv LNIG_*851.*.*   /jsdata/vnode/sr/roam_in/851
    mv LNIG_*871.*.*   /jsdata/vnode/sr/roam_in/871
    mv LNIG_*029.*.*   /jsdata/vnode/sr/roam_in/029
    mv LNIG_*931.*.*   /jsdata/vnode/sr/roam_in/931
    mv LNIG_*951.*.*   /jsdata/vnode/sr/roam_in/951
    mv LNIG_*991.*.*   /jsdata/vnode/sr/roam_in/991
    mv LNIG_*891.*.*   /jsdata/vnode/sr/roam_in/891
    mv LNIG_*898.*.*   /jsdata/vnode/sr/roam_in/898
    mv LNIG_*010.*.*   /jsdata/vnode/sr/roam_in/010
    mv LNIG_*571.*.*   /jsdata/vnode/sr/roam_in/571
    mv LNIG_*551.*.*   /jsdata/vnode/sr/roam_in/551
    mv LNIG_*591.*.*   /jsdata/vnode/sr/roam_in/591
    mv LNIG_*791.*.*   /jsdata/vnode/sr/roam_in/791
    mv LNIG_*531.*.*   /jsdata/vnode/sr/roam_in/531
    mv LNIG_*371.*.*   /jsdata/vnode/sr/roam_in/371
    mv LNIG_*027.*.*   /jsdata/vnode/sr/roam_in/027
    mv LNIG_*731.*.*   /jsdata/vnode/sr/roam_in/731
    mv LNIG_*020.*.*   /jsdata/vnode/sr/roam_in/020
    mv LNIG_*771.*.*   /jsdata/vnode/sr/roam_in/771
    sleep 10
done


select count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)!='898';
select substr(file_name,16,3), count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='898' group by substr(file_name,16,3);
select substr(file_name,16,3), count(1) from hi_qdcx.rm_qdcx where date_no='20190123' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='898' group by substr(file_name,16,3);
select file_name, count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='771' group by file_name order by file_name;
select file_name, count(1) from hi_qdcx.rm_qdcx where date_no='20190123' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='771' group by file_name order by file_name;
select file_name, count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='551' group by file_name order by file_name;
select file_name, count(1) from hi_qdcx.rm_qdcx where date_no='20190123' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='551' group by file_name order by file_name;
select file_name, count(1) from hi_qdcx.rm_qdcx where date_no='20190123' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='898' group by file_name order by file_name;
select file_name, count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='898' group by file_name order by file_name;
select count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='' and (cast(roam_st as int)-unix_timestamp(report_time,'yyyyMMddHHmmss'))>300;
select count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='' and (cast(roam_st as int)-unix_timestamp(report_time,'yyyyMMddHHmmss'))>300;
select count(1) from hi_qdcx.rm_qdcx where date_no='20190122' and substr(file_name,6,8)='20190122' and substr(file_name,16,3)='' and (cast(roam_st as int)-unix_timestamp(report_time,'yyyyMMddHHmmss'))>300;