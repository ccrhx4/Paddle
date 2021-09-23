#!/bin/bash

export PYTHON_INCLUDE_DIRS=/usr/include/python3.8
export PYTHON_LIBRARY=/usr/lib/python3.8/config-3.8-x86_64-linux-gnu
export SYCL_INC_DIR=/home/dcm/huanxing/dpcpp/linux_prod/compiler/linux/include

cmake .. -DPY_VERSION=3.8.10 -DSYCL_INC_DIR=${SYCL_INC_DIR} -DCMAKE_CXX_FLAGS=-I/${SYCL_INC_DIR} -DPYTHON_INCLUDE_DIR=${PYTHON_INCLUDE_DIRS} -DPYTHON_LIBRARY=${PYTHON_LIBRARY} -DWITH_GPU=ON -DWITH_TESTING=OFF -DCMAKE_BUILD_TYPE=Release
