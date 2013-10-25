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
        self.fobj.readline() #The second line is one minute before open

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        fields = curr_line.split(',');
        self.sec   = str2sec(fields[0])
        self.price = float(fields[2])
        cur_size   = int(fields[3])

        self.size = cur_size - self.prev_size
        self.prev_size = cur_size

        return self.sec

def main(fname1, fname2, fname3):
    dr1 = DataRecord(fname1)
    dr2 = DataRecord(fname2)
    dr3 = DataRecord(fname3)
    spread_name = "IF-butterfly"
    result = {}

    sec1 = dr1.getRecord()
    sec2 = dr2.getRecord()
    sec3 = dr3.getRecord()

    while 1:
        if sec1 == -1 or sec2 == -1 or sec3 == -1:
            break;
        elif sec1 < sec2 and sec1 < sec3:
            sec1 = dr1.getRecord()
        elif sec2 < sec1 and sec2 < sec3:
            sec2 = dr2.getRecord()
        elif sec3 < sec1 and sec3 < sec2:
            sec3 = dr3.getRecord()
        else:
            sp_price = dr1.price - 2 * dr2.price + dr3.price
            sp_size  = min(dr1.size, dr2.size, dr3.size)

            millisec = datetime.timedelta(milliseconds = sec1 * 100)
            tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
            tmp_date = tmp_date + millisec
            result[tmp_date] = [sp_price, sp_size]
            sec1 = dr1.getRecord()
            sec2 = dr2.getRecord()
            sec3 = dr3.getRecord()

    gplot.drawChart(result, spread_name)

def str2sec(time_stamp):
    hour    = int(time_stamp[1:3]) - 9
    minu    = int(time_stamp[4:6])
    sec     = int(time_stamp[7:9])
    milisec = int(time_stamp[10:13])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
