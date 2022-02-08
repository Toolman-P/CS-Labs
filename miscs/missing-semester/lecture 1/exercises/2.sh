#!/usr/bin/bash
function macro() {
    export MACRO=$(pwd)
}
function polo() {
    if [ $MACRO ];then
        cd $MACRO
    fi
}
