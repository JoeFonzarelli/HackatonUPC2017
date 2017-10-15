import openCv
import numpy as np


def get_sensor_information(sensor):
    headers = {'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75'}
    resp = requests.get("http://api.thingtia.cloud/data/provedor1/"+sensor, headers=headers)
    if not resp.ok:
        resp.raise_for_status()

    data = resp.json()
    out = data['observations'][0]["value"]
    out = out.split('*')
    out = out[1]
    time = data['observations'][0]["timestamp"]
    out.append(date)
    return out


def put_sensor_information(sensor, value):
    headers = {'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75'}
    resp = requests.put("http://api.thingtia.cloud/data/provedor1/"+sensor+"/"+str(value), headers=headers)
    if not resp.ok:
        resp.raise_for_status()


LAST_TIMES = [0, 0, 0]
SIZE = 60
BIN = 0
GARBAGE = 0
LUMINOSITY = 1
VERBOSE = True
if __name__ == '__main__':
    img = np.ones((SIZE, SIZE))
    _, last_bin = get_sensor_information("Bin1")
    _, last_garbage = get_sensor_information("Garbage1")
    _, last_luminosity = get_sensor_information("Luminosity1")
    level = get_sensor_information("Score1")[0]
    while True:
        bin, new_bin = get_sensor_information("Bin1")
        garbage, new_garbage = get_sensor_information("Garbage1")
        luminosity, new_luminosity = get_sensor_information("Luminosity1")
        if new_garbage != last_garbage:
            last_garbage = new_garbage
            if VERBOSE:
                print("It's dirty.")
            if GARBAGE == 0:
                level = max(0, level-1)
            else:
                level = min(6, level+GARBAGE)
            GARBAGE = 0

        if new_bin != last_bin:
            last_bin = new_bin
            if VERBOSE:
                print("The bin is full.")
            if BIN == 0:
                level = max(0, level-1)
            else:
                level = min(6, level+BIN)
            BIN = 0

        if new_luminosity != last_luminosity:
            last_luminosity = new_luminosity
            if VERBOSE:
                if luminosity == 1:
                    print("It's too dark.")
                else:
                    print("Light is useless.")
            if LUMINOSITY == 1:
                level = max(0, level-1)
            else:
                LUMINOSITY += (2*luminosity - 1)
                if LUMINOSITY > 1:
                    LUMINOSITY = 1
                    level = max(0, level-2)
                elif LUMINOSITY < 1:
                    LUMINOSITY = 0
                    level = max(0, level-2)
                else:
                    level = min(6, level+1)
            BIN = 0

        img_level = cv2.imread("./GameImgs/" + str(level) + ".png")
        cv2.imshow("BIN", img*BIN)
        cv2.imshow("GARBAGE", img*GARBAGE)
        cv2.imshow("LUMINOSITY", img*LUMINOSITY)
        cv2.imshow("LEVEL", img_level)
        cv2.waitKey(0)
        changes = raw_input("")
        if changes == "l0":
            LUMINOSITY = 0
        elif changes == "l1":
            LUMINOSITY = 1
        elif changes == "l2":
            LUMINOSITY = 2
        elif changes == "g0":
            GARBAGE = 0
        elif changes == "g1":
            GARBAGE = 1
        elif changes == "g2":
            GARBAGE = 2
        elif changes == "b0":
            BIN = 0
        elif changes == "b1":
            BIN = 1
        elif changes == "b2":
            BIN = 2
        elif changes == "vt":
            VERBOSE = True
        elif changes == "vf":
            VERBOSE = False
        elif changes == "e":
            cv2.imshow("EVOLUTION", cv2.imread("./GameImgs/evolution.jpg"))
            cv2.waitKey(2000)
