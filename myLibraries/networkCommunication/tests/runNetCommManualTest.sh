#!/bin/bash

# Manually runs the HelloWorldServer and the manual test here

../../build-Debug/protocol/helloWorldProtocol/HelloWorldServer/HelloWorldServer &

PID="$!"

sleep 1

../../build-Debug/communicationHandler/networkCommunication/netCommTest_Manual

kill $PID