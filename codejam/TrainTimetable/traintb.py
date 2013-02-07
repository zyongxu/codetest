import sys

def str2sec(time):
    h,m=time.split(':')
    return int(h)*60+int(m)

def schedule(fd):
    T=int(fd.readline())
    N=[int(n) for n in fd.readline().split(' ')]
    DA=[]
    AA=[]
    DB=[]
    AB=[]
    for i in range(N[0]):
        times = fd.readline().split(' ')
        DA.append(str2sec(times[0]))
        AA.append(str2sec(times[1])+T)
    for i in range(N[1]):
        times = fd.readline().split(' ')
        DB.append(str2sec(times[0]))
        AB.append(str2sec(times[1])+T)
    DA.sort()
    AA.sort()
    DB.sort()
    AB.sort()

    reta, retb = 0, 0
    lenda = len(DA)
    lenab = len(AB)
    a, b = 0, 0
    while a<lenda and b<lenab:
        if DA[a]<AB[b]:
            reta += 1
        else:
            b += 1
        a += 1
    reta += lenda-a if lenda-a>0 else 0

    lenaa = len(AA)
    lendb = len(DB)
    a, b = 0, 0
    while a<lenaa and b<lendb:
        if DB[b]<AA[a]:
            retb += 1
        else:
            a += 1
        b += 1
    retb += lendb-b if lendb-b>0 else 0

    ret = "%d %d" % (reta, retb)
    return ret

def main(filename):
    try:
        fd=open(filename, "r")
    except IOError as ioe:
        print "Cannot open the file"
        return 0

    N=int(fd.readline())
    for i in range(N):
        numOfTrains = schedule(fd)
        print "Case #%d: %s" % (i+1, numOfTrains)


if __name__=="__main__":
    main(sys.argv[1])
