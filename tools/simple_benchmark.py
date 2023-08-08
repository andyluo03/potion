import requests
import time

start_time = time.time_ns()
for i in range (0, 30000):
    x=requests.get('http://127.0.0.1:8080/test')
end_time = time.time_ns()
print(end_time - start_time)