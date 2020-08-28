#!/bin/bash
cvlc v4l2:// :v4l2-dev=/dev/video4 --sout="#transcode{vcodec=h264,acodec=mpga,ab=128,channels=2,samplerate=44100,scodec=none}:rtp{sdp=rtsp://:8554/seekThermal}"
raspivid -o - -t 0 -w 640 -h 360 -fps 25 | cvlc -vvv stream:///dev/stdin --sout '#standard{access=http, mux=ts, dst=:8090}' :demux=h264

