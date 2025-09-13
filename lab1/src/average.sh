#!/bin/bash

echo "Количество входных параметров  $#"
sum=0
total=$#
for i in "$@" 
do 
	sum=$((sum + i))
done
avg=$(( sum / total))
echo "среднее арифмитическое $avg"
