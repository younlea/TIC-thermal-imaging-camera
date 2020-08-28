#!/bin/bash
cvlc v4l2:// :v4l2-dev=/dev/video4 --sout="#transcode{vcodec=h264,acodec=mpga,ab=128,channels=2,samplerate=44100,scodec=none}:rtp{sdp=rtsp://:8554/seekThermal}"

