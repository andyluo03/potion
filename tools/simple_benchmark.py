import requests

def latency():
    URI = 'http://localhost:5000'
    ENDPOINT = '/test'
    REQ_NUM = 30000
    time = 0
    for i in range(REQ_NUM):
        r = requests.get(URI + ENDPOINT)
        # print(r.text)
        time += r.elapsed.total_seconds()
    return time / REQ_NUM * 1000, REQ_NUM
    
if __name__ == '__main__':
    lat, num = latency()
    print('Latency: {} ms per request, {} requests'.format(lat, num))