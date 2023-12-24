import re
import matplotlib.pyplot as plt
from matplotlib.pyplot import MultipleLocator

def draw(key_list, val_list):
    plt.xlabel('seqSize_IN_KB')
    plt.ylabel('avgCPI ')
    plt.title('RTX 3060(Low Config Version)')
    plt.plot(key_list, val_list)
    # # 标点
    # target_x = 32
    # ymin, ymax = plt.gca().get_ylim()
    # target_y = (ymin + ymax) / 2
    # plt.scatter(target_x, target_y, color='r')
    # plt.text(target_x+6, target_y-0.5, f'({target_x}, {target_y})', fontsize=10.5)

    # x_major_locator=MultipleLocator(10)
    # #把x轴的刻度间隔设置为1，并存在变量里
    # y_major_locator=MultipleLocator(0.5)
    # #把y轴的刻度间隔设置为10，并存在变量里
    # ax=plt.gca()
    # #ax为两条坐标轴的实例
    # ax.xaxis.set_major_locator(x_major_locator)
    # #把x轴的主刻度设置为1的倍数
    # ax.yaxis.set_major_locator(y_major_locator)
    # #把y轴的主刻度设置为10的倍数

    # plt.xlim(0, 300)
    # #把x轴的刻度范围设置为-0.5到11，因为0.5不满一个刻度间隔，所以数字不会显示出来，但是能看到一点空白
    # plt.ylim(16.0, 19.0)
    # #把y轴的刻度范围设置为-5到110，同理，-5不会标出来，但是能看到一点空白

    plt.savefig('res/res_L0CacheSize_my2_draw.png')
    plt.show()


def processTxt(res:str):
    key_list = []
    val_list = []
    for line in res.splitlines():
        tmp_list = line.split()
        key_list.append((int)(tmp_list[3].lstrip("0")))
        val_list.append((float)(tmp_list[2]))
    # print(key_list)
    # print(val_list)
    draw(key_list, val_list)


if __name__ == '__main__':
    with open('res/res_L0CacheSize_my.txt', 'r') as file:
        file.readline()
        res = file.read()
        processTxt(res)