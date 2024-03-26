from flask import Flask, request, jsonify
import ast
import serial
import threading
import time

app = Flask(__name__)

#thread infos
class BB8():
    def __init__(self):
        self.ser = serial.Serial("/dev/ttyACM0",baudrate=115200)
        self.x = "0.0"
        self.y = "0.0"
        self.msg = ""

    def updateCommands(self, x, y):
        self.x = x
        self.y = y
        
robot = BB8()


@app.route('/',methods=['POST'])
def query_example():
    data = "{"+ ast.literal_eval(str(request.get_data(), encoding="utf-8"))["body"]+"}"
    data = ast.literal_eval(data)
    #print(f"speed : {type(data['speed'])}")
    #print(data['speed'] == 0.0)
    if(data['speed'] == 0.0):
        data['speed'] = "0.0"
    #print(f"turn : {data['angle']}")
    if(data['angle'] == 0.0):
        data['angle'] = "0.0"
    robot.updateCommands(str(data['speed']), str(data['angle']))
    #print(robot.x)
    return request.get_data()

@app.after_request
def after(response):
    
    robot.msg = "<"+str(robot.x)+","+str(robot.y)+">" # "<" is the beginning of the message "," is the separator and ">" is the end of the message
    print(f"sending: {robot.msg}")   
    robot.ser.write(robot.msg.encode())
    return response

if __name__ == '__main__':
    # run app in debug mode on port 5000
    try:
        app.run(host="192.168.4.1", debug=False, port=5000)
            
    except Exception as e:
        print(e)