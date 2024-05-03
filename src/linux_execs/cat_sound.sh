#!/bin/bash

wget -P $HOME/Desktop -nc https://github.com/olincollege/VexWare/raw/main/src/linux_execs/angrycat.wav
amixer -D pulse sset Master 75%
aplay $HOME/Desktop/angrycat.wav
