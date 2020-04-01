
#!/usr/bin/env bash
n=1
while [ $n -le 130 ]
do
    if [ $n -lt 10 ]
    then
        m=00$n
    elif [ $n -lt 100 ]
    then
        m=0$n
    else
        m=$n
    fi

    touch -m LNIG_*025.00*$m.*; mv LNIG_*025.00*$m.*   /jsdata/vnode/sr/roam_in/025
    touch -m LNIG_*022.00*$m.*; mv LNIG_*022.00*$m.*   /jsdata/vnode/sr/roam_in/022
    touch -m LNIG_*021.00*$m.*; mv LNIG_*021.00*$m.*   /jsdata/vnode/sr/roam_in/021
    touch -m LNIG_*023.00*$m.*; mv LNIG_*023.00*$m.*   /jsdata/vnode/sr/roam_in/023
    touch -m LNIG_*311.00*$m.*; mv LNIG_*311.00*$m.*   /jsdata/vnode/sr/roam_in/311
    touch -m LNIG_*351.00*$m.*; mv LNIG_*351.00*$m.*   /jsdata/vnode/sr/roam_in/351
    touch -m LNIG_*471.00*$m.*; mv LNIG_*471.00*$m.*   /jsdata/vnode/sr/roam_in/471
    touch -m LNIG_*024.00*$m.*; mv LNIG_*024.00*$m.*   /jsdata/vnode/sr/roam_in/024
    touch -m LNIG_*451.00*$m.*; mv LNIG_*451.00*$m.*   /jsdata/vnode/sr/roam_in/451
    touch -m LNIG_*431.00*$m.*; mv LNIG_*431.00*$m.*   /jsdata/vnode/sr/roam_in/431
    touch -m LNIG_*971.00*$m.*; mv LNIG_*971.00*$m.*   /jsdata/vnode/sr/roam_in/971
    touch -m LNIG_*028.00*$m.*; mv LNIG_*028.00*$m.*   /jsdata/vnode/sr/roam_in/028
    touch -m LNIG_*851.00*$m.*; mv LNIG_*851.00*$m.*   /jsdata/vnode/sr/roam_in/851
    touch -m LNIG_*871.00*$m.*; mv LNIG_*871.00*$m.*   /jsdata/vnode/sr/roam_in/871
    touch -m LNIG_*029.00*$m.*; mv LNIG_*029.00*$m.*   /jsdata/vnode/sr/roam_in/029

    sleep 30
    let n++    #或者写作n=$(( $n + 1 ))
done




#!/usr/bin/env bash
n=1
while [ $n -le 58000 ]
do
    if [ $n -lt 10 ]
    then
        m=00$n
    elif [ $n -lt 100 ]
    then
        m=0$n
    else
        m=$n
    fi

    mv LNIG_*025.00*.*   /jsdata/vnode/sr/roam_in/025
    mv LNIG_*022.00*.*   /jsdata/vnode/sr/roam_in/022
    mv LNIG_*021.00*.*   /jsdata/vnode/sr/roam_in/021
    mv LNIG_*023.00*.*   /jsdata/vnode/sr/roam_in/023
    mv LNIG_*311.00*.*   /jsdata/vnode/sr/roam_in/311
    mv LNIG_*351.00*.*   /jsdata/vnode/sr/roam_in/351
    mv LNIG_*471.00*.*   /jsdata/vnode/sr/roam_in/471
    mv LNIG_*024.00*.*   /jsdata/vnode/sr/roam_in/024
    mv LNIG_*451.00*.*   /jsdata/vnode/sr/roam_in/451
    mv LNIG_*431.00*.*   /jsdata/vnode/sr/roam_in/431
    mv LNIG_*971.00*.*   /jsdata/vnode/sr/roam_in/971
    mv LNIG_*028.00*.*   /jsdata/vnode/sr/roam_in/028
    mv LNIG_*851.00*.*   /jsdata/vnode/sr/roam_in/851
    mv LNIG_*871.00*.*   /jsdata/vnode/sr/roam_in/871
    mv LNIG_*029.00*.*   /jsdata/vnode/sr/roam_in/029

    sleep 40
    let n++    #或者写作n=$(( $n + 1 ))
done



#    mv LNIG_*025.00*$m.*   /jsdata/vnode/sr/roam_in/025
#    mv LNIG_*022.00*$m.*   /jsdata/vnode/sr/roam_in/022
#    mv LNIG_*021.00*$m.*   /jsdata/vnode/sr/roam_in/021
#    mv LNIG_*023.00*$m.*   /jsdata/vnode/sr/roam_in/023
#    mv LNIG_*311.00*$m.*   /jsdata/vnode/sr/roam_in/311
#    mv LNIG_*351.00*$m.*   /jsdata/vnode/sr/roam_in/351
#    mv LNIG_*471.00*$m.*   /jsdata/vnode/sr/roam_in/471
#    mv LNIG_*024.00*$m.*   /jsdata/vnode/sr/roam_in/024
#    mv LNIG_*451.00*$m.*   /jsdata/vnode/sr/roam_in/451
#    mv LNIG_*431.00*$m.*   /jsdata/vnode/sr/roam_in/431
#    mv LNIG_*971.00*$m.*   /jsdata/vnode/sr/roam_in/971
#    mv LNIG_*028.00*$m.*   /jsdata/vnode/sr/roam_in/028
#    mv LNIG_*851.00*$m.*   /jsdata/vnode/sr/roam_in/851
#    mv LNIG_*871.00*$m.*   /jsdata/vnode/sr/roam_in/871
#    mv LNIG_*029.00*$m.*   /jsdata/vnode/sr/roam_in/029
#    mv LNIG_*931.00*$m.*   /jsdata/vnode/sr/roam_in/931
#    mv LNIG_*951.00*$m.*   /jsdata/vnode/sr/roam_in/951
#    mv LNIG_*991.00*$m.*   /jsdata/vnode/sr/roam_in/991
#    mv LNIG_*891.00*$m.*   /jsdata/vnode/sr/roam_in/891
#    mv LNIG_*898.00*$m.*   /jsdata/vnode/sr/roam_in/898
#    mv LNIG_*010.00*$m.*   /jsdata/vnode/sr/roam_in/010
#    mv LNIG_*571.00*$m.*   /jsdata/vnode/sr/roam_in/571
#    mv LNIG_*551.00*$m.*   /jsdata/vnode/sr/roam_in/551
#    mv LNIG_*591.00*$m.*   /jsdata/vnode/sr/roam_in/591
#    mv LNIG_*791.00*$m.*   /jsdata/vnode/sr/roam_in/791
#    mv LNIG_*531.00*$m.*   /jsdata/vnode/sr/roam_in/531
#    mv LNIG_*371.00*$m.*   /jsdata/vnode/sr/roam_in/371
#    mv LNIG_*027.00*$m.*   /jsdata/vnode/sr/roam_in/027
#    mv LNIG_*731.00*$m.*   /jsdata/vnode/sr/roam_in/731
#    mv LNIG_*020.00*$m.*   /jsdata/vnode/sr/roam_in/020
#    mv LNIG_*771.00*$m.*   /jsdata/vnode/sr/roam_in/771
[Instance_1]
10,22,21,
10, 20, 21, 22, 23, 24, 25, 27, 28, 29, 311, 351, 371, 431, 451, 471, 531, 551, 571, 591, 731,
771, 791, 851, 871, 891, 898, 931, 951, 971, 991}
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/010
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*010.*.*
###test
[Instance_2]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/022
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*022.*.*

[Instance_3]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/021
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*021.*.*

[Instance_4]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/023
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*023.*.*

[Instance_5]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/311
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*311.*.*


mv LNIG_*351.00*$m.*   /jsdata/vnode/sr/roam_in/351
mv LNIG_*471.00*$m.*   /jsdata/vnode/sr/roam_in/471
mv LNIG_*024.00*$m.*   /jsdata/vnode/sr/roam_in/024
mv LNIG_*451.00*$m.*   /jsdata/vnode/sr/roam_in/451
mv LNIG_*431.00*$m.*   /jsdata/vnode/sr/roam_in/431

[Instance_6]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/351
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*351.*.*

[Instance_7]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/471
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*471.*.*

[Instance_8]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/024
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*024.*.*

[Instance_9]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/451
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*451.*.*

[Instance_10]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/431
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*431.*.*

mv LNIG_*971.00*$m.*   /jsdata/vnode/sr/roam_in/971
mv LNIG_*028.00*$m.*   /jsdata/vnode/sr/roam_in/028
mv LNIG_*851.00*$m.*   /jsdata/vnode/sr/roam_in/851
mv LNIG_*871.00*$m.*   /jsdata/vnode/sr/roam_in/871
mv LNIG_*029.00*$m.*   /jsdata/vnode/sr/roam_in/029
[Instance_11]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/971
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*971.*.*

[Instance_12]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/028
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*028.*.*

[Instance_13]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/851
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*851.*.*

[Instance_14]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/871
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*871.*.*

[Instance_15]
#上传文件目录
InputPath=/jsdata/vnode/sr/roam_in/029
FOutPath=/jsdata/vnode/sr/roam_in/error/file
EOutPath=/jsdata/vnode/sr/roam_in/error/cdr
WorkPath=/jsdata/vnode/roam/work
#可以配置多个规则，以;分隔
FileRule=LNIG_*029.*.*