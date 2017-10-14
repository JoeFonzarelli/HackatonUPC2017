import requests
import json


def get_sensor_information(sensor):
    headers = {'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75'}
    resp = requests.get("http://api.thingtia.cloud/data/provedor1/"+sensor, headers=headers)
    if not resp.ok:
        resp.raise_for_status()

    data = json.loads(resp.content)
    out = data['observations'][0]["value"]
    out = out.split('*')
    out[0] = out[0].split(",")
    out[1] = bool(out[1])
    out[0][0] = float(out[0][0])
    out[0][1] = float(out[0][1])
    return out


data = get_sensor_information("luminosity1")
print(data)
