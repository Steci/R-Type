#!/bin/bash
rm client_build
mkdir build
cd build && cmake --preset=default ../ && make && cd ../
