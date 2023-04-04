from flask import Flask

app = Flask(__name__)

@app.route('/my-endpoint')
def my_endpoint():
    print('Received a request from a third-party device!')
    return 'Hello, world!'

if __name__ == '__main__':
    app.run(host='143.215.123.121', port=5000)
