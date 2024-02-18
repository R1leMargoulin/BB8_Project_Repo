from flask import Flask, request, jsonify
import ast

app = Flask(__name__)

@app.route('/',methods=['POST'])
def query_example():
    data = "{"+ ast.literal_eval(str(request.get_data(), encoding="utf-8"))["body"]+"}"
    data = ast.literal_eval(data)
    print(f"speed : {data['speed']}")
    print(f"turn : {data['angle']}")
    return request.get_data()

@app.after_request
def after(response):
    # todo with response
    return response

if __name__ == '__main__':
    # run app in debug mode on port 5000
    app.run(host="192.168.4.1", debug=False, port=5000)