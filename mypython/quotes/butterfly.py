#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
import re
import datetime
from localib import dyplot
from localib import util
from localib.data_record import DataRecord

def main(fname1, fname2, fname3):
    dr1 = DataRecord(fname1)
    dr2 = DataRecord(fname2)
    dr3 = DataRecord(fname3)
    spread_name = util.getProdFromFilename(fname1) + '-' +\
                  util.getProdFromFilename(fname2) + '-' +\
                  util.getProdFromFilename(fname3)
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

    dyplot.drawChart(result, spread_name)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
