#!/bin/bash
rm client_build
mkdir build
cd build && cmake ../ && make && cd ../
mv build/client/client ./client_build
