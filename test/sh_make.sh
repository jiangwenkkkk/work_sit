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


for line in `ls /data1/sr/roam_in/file/LNIG_*010.*.*`
do  
echo $line
i1=$(($i1+1))
echo $i1
if [ "$i1" -eq 60]
then
touch -m $line
mv $line /data1/sr/roam_in/010/
i1=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*020.*.*`
do  
echo $line
i2=$(($i2+1))
echo $i2
if [ "$i1" -eq 5]
then
touch -m $line
mv $line /data1/sr/roam_in/020/
i2=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*021.*.*`
do  
echo $line
i3=$(($i3+1))
echo $i3
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/021/
i3=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*022.*.*`
do  
echo $line
i4=$(($i4+1))
echo $i4
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/022/
i4=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*023.*.*`
do  
echo $line
i5=$(($i5+1))
echo $i5
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/023/
i5=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*024.*.*`
do  
echo $line
i6=$(($i6+1))
echo $i6
if [ "$i1" -eq 15]
then
touch -m $line
mv $line /data1/sr/roam_in/024/
i6=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*025.*.*`
do  
echo $line
i7=$(($i7+1))
echo $i7
if [ "$i1" -eq 15]
then
touch -m $line
mv $line /data1/sr/roam_in/025/
i7=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*027.*.*`
do  
echo $line
i8=$(($i8+1))
echo $i8
if [ "$i1" -eq 15]
then
touch -m $line
mv $line /data1/sr/roam_in/027/
i8=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*028.*.*`
do  
echo $line
i9=$(($i9+1))
echo $i9
if [ "$i1" -eq 15]
then
touch -m $line
mv $line /data1/sr/roam_in/028/
i9=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*029.*.*`
do  
echo $line
i10=$(($i10+1))
echo $i10
if [ "$i1" -eq 15]
then
touch -m $line
mv $line /data1/sr/roam_in/029/
i10=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*311.*.*`
do  
echo $line
i11=$(($i11+1))
echo $i11
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/311/
i11=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*351.*.*`
do  
echo $line
i12=$(($i12+1))
echo $i12
if [ "$i1" -eq 20]
then
touch -m $line
mv $line /data1/sr/roam_in/351/
i12=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*371.*.*`
do  
echo $line
i13=$(($i13+1))
echo $i13
if [ "$i1" -eq 60]
then
touch -m $line
mv $line /data1/sr/roam_in/371/
i13=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*431.*.*`
do  
echo $line
i14=$(($i14+1))
echo $i14
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/431/
i14=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*451.*.*`
do  
echo $line
i15=$(($i15+1))
echo $i15
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/451/
i15=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*471.*.*`
do  
echo $line
i16=$(($i16+1))
echo $i16
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/471/
i16=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*531.*.*`
do  
echo $line
i17=$(($i17+1))
echo $i17
if [ "$i1" -eq 60]
then
touch -m $line
mv $line /data1/sr/roam_in/531/
i17=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*551.*.*`
do  
echo $line
i18=$(($i18+1))
echo $i18
if [ "$i1" -eq 20]
then
touch -m $line
mv $line /data1/sr/roam_in/551/
i18=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*571.*.*`
do  
echo $line
i19=$(($i19+1))
echo $i19
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/571/
i19=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*591.*.*`
do  
echo $line
i20=$(($i20+1))
echo $i20
if [ "$i1" -eq 60]
then
touch -m $line
mv $line /data1/sr/roam_in/591/
i20=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*731.*.*`
do  
echo $line
i21=$(($i21+1))
echo $i21
if [ "$i1" -eq 10]
then
touch -m $line
mv $line /data1/sr/roam_in/731/
i21=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*771.*.*`
do  
echo $line
i22=$(($i22+1))
echo $i22
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/771/
i22=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*791.*.*`
do  
echo $line
i23=$(($i23+1))
echo $i23
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/791/
i23=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*851.*.*`
do  
echo $line
i24=$(($i24+1))
echo $i24
if [ "$i1" -eq 60]
then
touch -m $line
mv $line /data1/sr/roam_in/851/
i24=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*871.*.*`
do  
echo $line
i25=$(($i25+1))
echo $i25
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/871/
i25=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*891.*.*`
do  
echo $line
i26=$(($i26+1))
echo $i26
if [ "$i1" -eq 60]
then
touch -m $line
mv $line /data1/sr/roam_in/891/
i26=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*898.*.*`
do  
echo $line
i27=$(($i27+1))
echo $i27
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/898/
i27=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*931.*.*`
do  
echo $line
i28=$(($i28+1))
echo $i28
if [ "$i1" -eq 20]
then
touch -m $line
mv $line /data1/sr/roam_in/931/
i28=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*951.*.*`
do  
echo $line
i29=$(($i29+1))
echo $i29
if [ "$i1" -eq 30]
then
touch -m $line
mv $line /data1/sr/roam_in/951/
i29=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*971.*.*`
do  
echo $line
i30=$(($i30+1))
echo $i30
if [ "$i1" -eq 20]
then
touch -m $line
mv $line /data1/sr/roam_in/971/
i30=0
break
else
break
fi
done

for line in `ls /data1/sr/roam_in/file/LNIG_*991.*.*`
do  
echo $line
i31=$(($i31+1))
echo $i31
if [ "$i1" -eq 20]
then
touch -m $line
mv $line /data1/sr/roam_in/991/
i31=0
break
else
break
fi
done

echo "sleep"
sleep 1
done