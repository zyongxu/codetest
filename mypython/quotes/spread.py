#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
import re
import gplot
import dyplot
import datetime
import util
from data_record import DataRecord

def main(fname1, fname2):
    dr1 = DataRecord(fname1)
    dr2 = DataRecord(fname2)
    spread_name = util.getProdFromFilename(fname1) + '-' +\
                  util.getProdFromFilename(fname2)
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

    dyplot.drawChart(result, spread_name)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
