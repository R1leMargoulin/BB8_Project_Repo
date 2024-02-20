from flask import Flask, request, jsonify
import ast
import serial
import threading
import time

app = Flask(__name__)

#thread infos
class BB8(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.ser = serial.Serial("/dev/ttyAMA0",baudrate=9600)
        self.x = "0.0"
        self.y = "0.0"

    def run(self):
        
        while(True):
            msg = str(self.x)+","+str(self.y)+",\n"
            self.ser.write(msg.encode())
            time.sleep(0.02)

    def updateCommands(self, x, y):
        self.x = x
        self.y = y
        
robot = BB8()


@app.route('/',methods=['POST'])
def query_example():
    data = "{"+ ast.literal_eval(str(request.get_data(), encoding="utf-8"))["body"]+"}"
    data = ast.literal_eval(data)
    print(f"speed : {data['speed']}")
    if(data['speed'] == 0):
        data['speed'] = "0.0"
    print(f"turn : {data['angle']}")
    if(data['angle'] == 0):
        data['angle'] = "0.0"
    robot.updateCommands(str(data['speed']), str(data['angle']))
    return request.get_data()

@app.after_request
def after(response):
    # todo with response
    return response

if __name__ == '__main__':
    # run app in debug mode on port 5000
    try:
        robot.start()
        app.run(host="192.168.4.1", debug=False, port=5000)
    except Exception as e:
        print(e)