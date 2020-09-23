#!/bin/bash
cvlc v4l2:// :v4l2-dev=/dev/video4 --sout="#transcode{vcodec=h264,venc=x264{preset=ultrafast,tune=zerolatency,intra-refresh,lookahead=10,keyint=15},acodec=mpga,ab=128,channels=2,samplerate=44100,scodec=none}:rtp{sdp=rtsp://:8554/seekThermal}" &
#ffmpeg -f x11grab -s 320x240 -preset ultrafast -tune zerolatency -r 50 -vcodec mpeg2video -b:v 8000 -f rtp rtp://:8554/seekThermal &

raspivid -o - -t 0 -w 640 -h 360 -fps 25 | cvlc -vvv stream:///dev/stdin --sout '#standard{access=http, mux=ts, dst=:8090}' :demux=h264 &


