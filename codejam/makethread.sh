#!/bin/bash

STR="g++ -g -I${1} -I. -lboost main.cpp"
$STR
