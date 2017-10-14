import requests
import json
import numpy as np
import cv2
import datetime

HEADER = {'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75'}
COMPONENTS =[]
TOT_COMPONENTS = 100
SIZE = 5

LAT_TOP_LEFT = 41.405251  # y component
LONG_TOP_LEFT = 2.166431  # x component
LAT_BOTTOM_LEFT = 41.398392
LONG_BOTTOM_LEFT = 2.175421
LAT_BOTTOM_RIGHT = 41.405183
LONG_BOTTOM_RIGHT = 2.184509
THRESHOLD = 5

pts1 = np.float32([[0, SIZE], [0, 0], [SIZE, 0]])
pts2 = np.float32([[LONG_TOP_LEFT, LAT_TOP_LEFT], [LONG_BOTTOM_LEFT, LAT_BOTTOM_LEFT],
                   [LONG_BOTTOM_RIGHT, LAT_BOTTOM_RIGHT]])

M = cv2.getAffineTransform(pts1, pts2)
M1 = cv2.getAffineTransform(pts2, pts1)

GARBAGE_MAP = np.zeros((SIZE, SIZE))
BIN_MAP = np.zeros((SIZE, SIZE))
LUMINOSITY = 0.5
MID_DAY = 1
TIME_PASSED = 2
HOW_DIRTY = np.random.rand(SIZE, SIZE)
URL = "http://api.thingtia.cloud/data/provedor1/"


def get_sensor_information(sensor):
    global HEADER
    resp = requests.get("http://api.thingtia.cloud/data/provedor1/"+sensor, headers=HEADER)
    if not resp.ok:
        resp.raise_for_status()

    data = resp.json()
    out = data['observations'][0]["value"]
    out = out.split('*')
    out[0] = out[0].split(",")
    out[1] = bool(out[1])
    out[0][0] = float(out[0][0])
    out[0][1] = float(out[0][1])
    time = data['observations'][0]["timestamp"]
    time = time.split("T")
    time[1] = time[1].split(":")
    time[0] = time[0].split("/")
    date = [int(time[0][2]), int(time[0][1]), int(time[0][0]), int(time[1][0]), int(time[1][1]), int(time[1][2])]
    out.append(date)
    return out


class Component(object):
    def __init__(self, index):
        x = int(np.random.rand() * SIZE)
        y = int(np.random.rand() * SIZE)
        self.pos = np.array([[x, y]])
        self.prob_post_lumin = np.random.rand()*0.5
        self.prob_post_garb = np.random.rand()
        self.prob_post_bin = np.random.rand()
        self.index = index

    def post(self):
        global HEADER, URL, BIN_MAP, GARBAGE_MAP, LUMINOSITY
        new_pos = M * (np.matrix([[np.random.rand()], [np.random.rand()], [1]])+np.matrix([[self.pos[0][0]], [self.pos[0][1]], [1]]))
        x = new_pos[0]
        y = new_pos[1]
        if BIN_MAP[self.pos[0][1]][self.pos[0][0]] > self.prob_post_bin:
            path_name = "/{0:},{1:}*{2:}".format(x, y, BIN_MAP[self.y_pos][self.x_pos] > 1)
            path_name = URL+"Bin"+str(self.index)+path_name
            requests.put(path_name, headers=HEADER)
        if GARBAGE_MAP[self.pos[0][1]][self.pos[0][0]] > self.prob_post_garb:
            path_name = "/{0:},{1:}*{2:}".format(x, y, GARBAGE_MAP[self.y_pos][self.x_pos] > 1)
            path_name = URL + "Garbage" + str(self.index) + path_name
            requests.put(path_name, headers=HEADER)
        if abs(1-LUMINOSITY) > self.prob_post_lumin:
            path_name = "/{0:},{1:}*{2:}".format(x, y, LUMINOSITY < 0.5)
            path_name = URL+"Luminosity"+str(self.index)+path_name
            requests.put(path_name, headers=HEADER)


def function_horvel():
    global HEADER, SIZE, LUMINOSITY, GARBAGE_MAP, BIN_MAP
    now = datetime.datetime.now()
    now_y = now.year
    now_m = now.month
    now_d = now.day
    now_h = now.hour
    now_mi= now.minute
    now_s = now.second
    lum_reaction = 0
    garb_reaction = np.zeros((SIZE, SIZE))
    bin_reaction = np.zeros((SIZE, SIZE))
    for i in range(1, TOT_COMPONENTS+1):
        resp = get_sensor_information("Luminosity"+str(i))
        y, m, d, h, mi, s = resp[2]
        if now_y - y > 0.1:
            pass
        elif now_m - m > 0.1:
            pass
        elif now_d - d > 0.1:
            pass
        elif now_h - h > 0.1:
            pass
        elif now_mi - mi > 0.1:
            lum_reaction += (resp[1] * 2 - 1) * 2**((mi-now_mi)/150)
        elif now_s -s > 0.1:
            lum_reaction += (resp[1] * 2 - 1) * 2**((s-now_s)/9000)  # 9000 = 60 * 150

        resp = get_sensor_information("Garbage"+str(i))
        y, m, d, h, mi, s = resp[2]
        pos = M1 * np.matrix([[resp[0][1]], [resp[0][0]], [1]])
        row = int(pos[0])
        if row >= SIZE:
            row = SIZE - 1
        elif row < 0:
            row = 0
        col = int(pos[1])
        if col >= SIZE:
            col = SIZE - 1
        elif col < 0:
            col = 0
        if now_y - y > 0.1:
            pass
        elif now_m - m > 0.1:
            pass
        elif now_d - d > 0.1:
            pass
        elif now_h - h > 0.1:
            garb_reaction[col][row] += resp[1] * 2**(mi-now_mi)
        elif now_mi - mi > 0.1:
            garb_reaction[col][row] += resp[1] * 2**((mi-now_mi)/24)  # 24 hours a day
        elif now_s - s > 0.1:
            garb_reaction[col][row] += resp[1] * 2**((s-now_s)/9000)  # 9000 = 60 * 150

        resp = get_sensor_information("Garbage"+str(i))
        y, m, d, h, mi, s = resp[2]
        pos = M1 * np.matrix([[resp[0][1]], [resp[0][0]], [1]])
        row = int(pos[0])
        if row >= SIZE:
            row = SIZE - 1
        elif row < 0:
            row = 0
        col = int(pos[1])
        if col >= SIZE:
            col = SIZE - 1
        elif col < 0:
            col = 0
        if now_y - y > 0.1:
            pass
        elif now_m - m > 0.1:
            pass
        elif now_d - d > 0.1:
            pass
        elif now_h - h > 0.1:
            bin_reaction[col][row] += resp[1] * 2**(mi-now_mi)
        elif now_mi - mi > 0.1:
            bin_reaction[col][row] += resp[1] * 2**((mi-now_mi)/24)  # 24 hours a day
        elif now_s - s > 0.1:
            bin_reaction[col][row] += resp[1] * 2**((s-now_s)/9000)  # 9000 = 60 * 150

    LUMINOSITY += lum_reaction
    if LUMINOSITY > 1:
        LUMINOSITY = 1
    elif LUMINOSITY < 0:
        LUMINOSITY = 0

    thresholding = np.vectorize(lambda x: (0 if x > THRESHOLD else 1))
    garb_reaction = thresholding(garb_reaction)
    bin_reaction = thresholding(bin_reaction)
    GARBAGE_MAP = np.dot(bin_reaction, BIN_MAP)
    BIN_MAP = np.dot(garb_reaction, GARBAGE_MAP)


def show_imgs():
    img = np.zeros((10 * SIZE, 10 * SIZE, 3))
    img[:, :, 0] = cv2.resize(np.ones([SIZE, SIZE]) * LUMINOSITY, (10 * SIZE, 10 * SIZE)) * 255
    img[:, :, 1] = cv2.resize(GARBAGE_MAP, (10 * SIZE, 10 * SIZE)) * 255
    img[:, :, 2] = cv2.resize(BIN_MAP, (10 * SIZE, 10 * SIZE)) * 255

    cv2.imshow("image", img)
    cv2.waitKey(250)


def three_hours():
    global LUMINOSITY, MID_DAY, COMPONENTS, TIME_PASSED
    TIME_PASSED += 1
    LUMINOSITY += 0.25 * MID_DAY
    if not TIME_PASSED % 4:
        TIME_PASSED = 0
        MID_DAY *= -1
    if LUMINOSITY > 1:
        LUMINOSITY = 1
    elif LUMINOSITY < 0:
        LUMINOSITY = 0

    for component in COMPONENTS:
        component.post()

    function_horvel()
    show_imgs()


def get_dirty():
    global BIN_MAP, GARBAGE_MAP, HOW_DIRTY
    get_top = np.vectorize(lambda x: (x if x<1 else 1))
    BIN_MAP += HOW_DIRTY * np.random.rand(SIZE, SIZE)/7
    GARBAGE_MAP += HOW_DIRTY * np.random.rand(SIZE, SIZE)/14
    BIN_MAP = get_top(BIN_MAP)
    GARBAGE_MAP = get_top(GARBAGE_MAP)


if __name__ == '__main__':
    COMPONENTS = [Component(i) for i in range(2, TOT_COMPONENTS+1)]
    while True:
        for i in range(8):
            three_hours()
        get_dirty()
