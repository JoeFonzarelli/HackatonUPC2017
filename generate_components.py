import requests
import json
import numpy as np

import datetime
now = datetime.datetime.now()
y = now.year
headers = {'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75'}
resp = requests.get("http://api.thingtia.cloud/data/provedor1/Luminosity1", headers=headers)
# resp = requests.get(URL+"Luminosity1", headers=HEADER)
if not resp.ok:
    resp.raise_for_status()

# print(resp)
print(resp.content)
