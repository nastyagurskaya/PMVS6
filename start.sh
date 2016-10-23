sudo insmod timer.ko

sudo chmod a+w+r /sys/timer/interval

echo "#2"
echo "2" > /sys/timer/interval

sleep 5
echo 0 > /sys/timer/interval

sudo rmmod timer
