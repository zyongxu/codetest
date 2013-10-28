#!/usr/bin/python

import sys
import re
import os
import math

class PriceQueue:
    def __init__(self, qlen):
        self.__qlen     = qlen
        self.__elems    = []
        self.max_diff   = 0
        self.aprox_line = 0

    def getDiff(self):
        return max(self.__elems) - min(self.__elems)

    def push(self, price, line_num):
        self.__elems.append(price)
        if (len(self.__elems) > self.__qlen):
            del self.__elems[0]

        if (self.getDiff() > self.max_diff):
            self.max_diff = self.getDiff();
            self.aprox_line = line_num

class DataRecord:
    def __init__(self, filename):
        self.fobj             = open(filename, 'rb')
        self.cur_line         = 1
        self.half_sec         = PriceQueue(2)
        self.one_sec          = PriceQueue(3)
        self.one_and_half_sec = PriceQueue(4)
        self.two_sec          = PriceQueue(5)

        self.fobj.readline() #The first line is a summary of yesterday
        self.fobj.readline() #do a favor to IF

    def readLine(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        fields = curr_line.split(',');
        cur_price = float(fields[2])
        self.half_sec.push(cur_price, self.cur_line)
        self.one_sec.push(cur_price, self.cur_line)
        self.one_and_half_sec.push(cur_price, self.cur_line)
        self.two_sec.push(cur_price, self.cur_line)

        self.cur_line += 1
        return 0

def main(fname):
    dr = DataRecord(fname)

    while 1:
        if dr.readLine() < 0:
            break

    print dr.half_sec.max_diff, dr.half_sec.aprox_line
    print dr.one_sec.max_diff, dr.one_sec.aprox_line
    print dr.one_and_half_sec.max_diff, dr.one_and_half_sec.aprox_line
    print dr.two_sec.max_diff, dr.two_sec.aprox_line

if __name__ == "__main__":
    main(sys.argv[1])
