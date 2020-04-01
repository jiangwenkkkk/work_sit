#!/usr/bin/env bash
i1=0
i2=0
i3=0
i4=0
i5=0
i6=0
i7=0
i8=0
i9=0
i10=0
i11=0
i12=0
i13=0
i14=0
i15=0
i16=0
i17=0
i18=0
i19=0
i20=0
i21=0
i22=0
i23=0
i24=0
i25=0
i26=0
i27=0
i28=0
i29=0
i30=0
i31=0

while true
do

for line in `ls /data1/sr/roam_in/file/LNIG_*025.*.*`
do  
echo $line
i1=$(($i1+1))
echo $i1
if [ "$i1" -eq 5 ]
then
touch -m $line
mv $line /data1/sr/roam_in/025/
i1=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*025.*.*`
do
echo $line
i1=$(($i1+1))
echo $i1
if [ "$i1" -eq 5 ]
then
touch -m $line
mv $line /data1/sr/roam_in/025/
i1=0
break
else
break
fi
done




echo "sleep"
sleep 1
done

