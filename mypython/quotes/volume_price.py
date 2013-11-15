#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
import re
import dyplot
import datetime
import os
from data_record import DataRecord

def main(fname1):
    dr1 = DataRecord(fname1)
    spread_name = os.path.basename(fname1)
    result = {}

    sec1 = dr1.getRecord()

    while 1:
        sp_price = dr1.price
        sp_size  = dr1.size
        millisec = datetime.timedelta(milliseconds = sec1 * 100)
        tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
        tmp_date = tmp_date + millisec
        result[tmp_date] = [sp_price, sp_size]
        sec1 = dr1.getRecord()
        if sec1 == -1:
            break

    dyplot.drawChart(result, spread_name)

if __name__ == "__main__":
    main(sys.argv[1])
