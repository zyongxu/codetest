def str2sec(time_stamp):
    hour    = int(time_stamp[0:2]) - 9
    minu    = int(time_stamp[3:5])
    sec     = int(time_stamp[6:8])
    milisec = int(time_stamp[9:12])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100
