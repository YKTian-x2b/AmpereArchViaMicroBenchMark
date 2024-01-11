import re
import os
import subprocess
import matplotlib.pyplot as plt

def draw(key_list, val_list):
    plt.xlabel('Array size in MB')
    plt.ylabel('Avg Latency(clocks)')
    plt.title('RTX 3060(Low Config Version)')
    plt.plot(key_list, val_list)
    # 标点
    target_x = 32
    ymin, ymax = plt.gca().get_ylim()
    target_y = (ymin + ymax) / 2
    plt.scatter(target_x, target_y, color='r')
    plt.text(target_x+6, target_y-0.5, f'({target_x}, {target_y})', fontsize=10.5)
    plt.savefig('res/L1_TLB_detect_res.png')
    plt.show()


def processTxt(res:str):
    key_list = []
    val_list = []
    for line in res.splitlines():
        r = re.search('ARR_SIZE_IN_MB: (.*), Global Mem access latency: (.*) cycles', line)
        if r is not None:
            key_list.append(int(r.groups()[0]))
            val_list.append(float(r.groups()[1]))
    print(key_list)
    print(val_list)
    draw(key_list, val_list)


if __name__ == '__main__':
    os.system('nvidia-smi -ac 7000,1702')

    projectPath = '/home/yujixuan/kaiPro/GitHubLocal/AmpereArchViaMicroBenchmark/AmpereArchViaMicroBenchMark/'
    res = subprocess.check_output(projectPath + 'GlobalMem_Bandwidth_Latency/res/L1_TLB_detect')
    with open('res/L1_TLB_detect_res.txt', 'w') as file:
        file.write(res.decode())
    with open('res/L1_TLB_detect_res.txt', 'r') as file:
        res = file.read()
        processTxt(res)