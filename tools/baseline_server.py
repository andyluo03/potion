from flask import Flask

app = Flask(__name__)

@app.route('/test')
def handle():
    return "test"

if __name__ == "__main__":
    app.run(port=8080)