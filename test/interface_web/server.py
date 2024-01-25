from flask import Flask, request

app = Flask(__name__)

@app.route('/',methods=['POST'])
def query_example():
    return request.get_data()

@app.after_request
def after(response):
    # todo with response
    print(response.get_data())
    return response

if __name__ == '__main__':
    # run app in debug mode on port 5000
    app.run(debug=True, port=5000)