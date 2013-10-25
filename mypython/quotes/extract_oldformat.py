#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
import re
import gplot
import datetime
import os

class DataRecord:
    def __init__(self, filename):
        self.fobj = open(filename, 'rb')
        self.sec       = 0
        self.price     = 0
        self.size      = 0
        self.prev_size = 0
        self.fobj.readline() #The first line is a summary of yesterday
        self.fobj.readline() #do a favor to IF

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        self.sec = str2sec(curr_line)
        [self.price, cur_size] = priceAndSize(curr_line)

        self.size = cur_size - self.prev_size
        self.prev_size = cur_size

        return self.sec

def main(fname1, fname2):
    dr1 = DataRecord(fname1)
    dr2 = DataRecord(fname2)
    spread_name = os.path.basename(fname1) + '-' + os.path.basename(fname2)
    result = {}

    sec1 = dr1.getRecord()
    sec2 = dr2.getRecord()

    while 1:
        if sec1 == -1 or sec2 == -1:
            break;
        elif sec1 < sec2:
            sec1 = dr1.getRecord()
        elif sec2 < sec1:
            sec2 = dr2.getRecord()
        else:
            sp_price = dr1.price - dr2.price
            sp_size  = min(dr1.size, dr2.size)

            millisec = datetime.timedelta(milliseconds = sec1 * 100)
            tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
            tmp_date = tmp_date + millisec
            result[tmp_date] = [sp_price, sp_size]
            sec1 = dr1.getRecord()
            sec2 = dr2.getRecord()

    gplot.drawChart(result, spread_name)
    #for k, v in sorted(result.iteritems()):
    #    print k, v

def str2sec(time_stamp):
    hour    = int(time_stamp[1:3]) - 9
    minu    = int(time_stamp[4:6])
    sec     = int(time_stamp[7:9])
    milisec = int(time_stamp[10:13])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

def priceAndSize(str1):
    fields = str1.split(' ', 4)
    price = float(fields[1])
    size  = int(fields[2])

    return [price, size]

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
