#!/usr/bin/python

import sys
import re
import datetime
import os

class DataRecord:
    def __init__(self, filename, tick):
        self.fobj = open(filename, 'rb')
        self.sec       = 0
        self.prev_bid  = 0
        self.bid_slip  = 0
        self.prev_ask  = 0
        self.ask_slip  = 0
        self.TICK      = float(tick)
        self.fobj.readline() #The first line is a summary of yesterday
        self.fobj.readline() #do a favor to IF

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        fields = curr_line.split(',');
        self.sec = str2sec(fields[0])
        mds = fields[1].split(' ')
        cur_bb = float("{0:.1f}".format(float(mds[0])))
        cur_ba = float("{0:.1f}".format(float(mds[2])))
        self.bid_slip = float("{0:.1f}".format(self.prev_bid - cur_bb))
        self.ask_slip = float("{0:.1f}".format(self.prev_ask - cur_ba))
        self.prev_bid = float("{0:.1f}".format(cur_bb + self.TICK))
        self.prev_ask = float("{0:.1f}".format(cur_ba - self.TICK))

        return self.sec

def main(fname1, tick):
    dr1 = DataRecord(fname1, tick)
    spread_name = os.path.basename(fname1)

    sec1 = dr1.getRecord()
    out_csv = open(spread_name+".csv", 'w')
    out_csv.write("time,bid,ask\n")

    while 1:
        sec1 = dr1.getRecord()
        if sec1 == -1:
            break

        millisec = datetime.timedelta(milliseconds = sec1 * 100)
        tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
        tmp_date = tmp_date + millisec
        csv_line = "{},{},{}\n".format(tmp_date, dr1.bid_slip, dr1.ask_slip)
        out_csv.write(csv_line)

def str2sec(time_stamp):
    hour    = int(time_stamp[0:2]) - 9
    minu    = int(time_stamp[3:5])
    sec     = int(time_stamp[6:8])
    milisec = int(time_stamp[9:12])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
