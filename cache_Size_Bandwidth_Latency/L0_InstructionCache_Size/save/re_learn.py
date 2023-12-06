import re

n_FFMA_seqs = 128

def parseResult(res:str):
    avgCycles = 0.0
    for line in res.splitlines():
        r = re.search('avg CPI: (.*)', line)
        if r is not None:
            avgCycles = float(r.groups()[0])
            global n_FFMA_seqs
            print(f'avgCycles:{avgCycles:8.4f},  avgCPI:{avgCycles/n_FFMA_seqs:8.4f}')
            # t = float(r.groups()[1])
            # tlist.append(t)

            # nt += 1
            # tsum += t
            # tsq += t*t
        
    # nt = 0      
    # tsum = 0.0
    # tsq = 0.0
    # tres = ''
    # tlist = []

    # for line in res.splitlines():
    #     r = re.search('Test(.*):(.*)ms', line)
    #     if r is not None:
    #         t = float(r.groups()[1])
    #         tlist.append(t)

    #         nt += 1
    #         tsum += t
    #         tsq += t*t
        
    #     r2 = re.search(r'res\[\s*0\]\s*:(.*)', line)
    #     if r2 is not None:
    #         tres = r2.groups()[0].strip()

    # tavg = tsum/nt
    # tstd = math.sqrt(tsq/nt - tavg*tavg)

    # sfull = '[' + (', '.join(['%8.3f'%t for t in tlist])) + ']'
    # return tavg, tstd, tres, sfull

if __name__ == '__main__':
    with open('/opt/kaiProjects/MicroBenchmark/cache_Size_Throughput_Latency/L0_Cache_Size/save/res_L0CacheSize.txt') as file:
        res = file.read()
        parseResult(res)