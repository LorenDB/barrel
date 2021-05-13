#!/bin/bash
cd src
clang-format -i *.cpp *.h
cd instructions
clang-format -i *.cpp *.h
cd ../..
