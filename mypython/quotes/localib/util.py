import os
import datetime

def str2sec(time_stamp):
    hour    = int(time_stamp[0:2]) - 9
    minu    = int(time_stamp[3:5])
    sec     = int(time_stamp[6:8])
    milisec = int(time_stamp[9:12])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

def sec2str(sec):
    millisec = datetime.timedelta(milliseconds = sec * 100)
    tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
    return tmp_date + millisec

def getProdFromFilename(fname):
    return os.path.splitext(os.path.basename(fname))[0]
