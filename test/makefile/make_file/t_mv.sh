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

   echo LNIG_*025.00*$m.*   /jsdata/vnode/sr/roam_in/025
   echo LNIG_*022.00*$m.*   /jsdata/vnode/sr/roam_in/022
   echo LNIG_*021.00*$m.*   /jsdata/vnode/sr/roam_in/021
   echo LNIG_*023.00*$m.*   /jsdata/vnode/sr/roam_in/023
   echo LNIG_*311.00*$m.*   /jsdata/vnode/sr/roam_in/311
   echo LNIG_*351.00*$m.*   /jsdata/vnode/sr/roam_in/351
   echo LNIG_*471.00*$m.*   /jsdata/vnode/sr/roam_in/471
   echo LNIG_*024.00*$m.*   /jsdata/vnode/sr/roam_in/024
   echo LNIG_*451.00*$m.*   /jsdata/vnode/sr/roam_in/451
   echo LNIG_*431.00*$m.*   /jsdata/vnode/sr/roam_in/431
   echo LNIG_*971.00*$m.*   /jsdata/vnode/sr/roam_in/971
   echo LNIG_*028.00*$m.*   /jsdata/vnode/sr/roam_in/028
   echo LNIG_*851.00*$m.*   /jsdata/vnode/sr/roam_in/851
   echo LNIG_*871.00*$m.*   /jsdata/vnode/sr/roam_in/871
   echo LNIG_*029.00*$m.*   /jsdata/vnode/sr/roam_in/029

#    sleep 60
    let n++    #或者写作n=$(( $n + 1 ))
done