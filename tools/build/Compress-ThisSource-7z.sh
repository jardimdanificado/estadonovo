#!/bin/bash
current_time=$(date "%y%m%d%H%M%S")

7z a -t7z -m0=lzma2 -mx=9 -aoa -mfb=64 -md=32m -ms=on -mhe ./src_$current_time.7z ../../*
