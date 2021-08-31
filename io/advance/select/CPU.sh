#!/bin/bash

total=$(cat /proc/meminfo|grep 'MemTotal'|awk '{printf $2}')

echo $total

