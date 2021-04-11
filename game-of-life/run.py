from flask import Flask, jsonify, render_template, request, Response
from game_of_life import getNextState
import numpy as np
import json
import time

import random

app = Flask(__name__)

@app.route("/")
def home():
    global config
    with open('./configuration.json') as f:
        config = json.load(f)
    return render_template("index.html", config=config)

@app.route("/config", methods=['POST'])
def showPattern():
    global config
    global initial_config

    key = request.form['myPattern']
    rows, cols = int(request.form["rows"]), int(request.form["cols"])
    
    if key == "random":
        state = [[random.randint(0,1) for x in range(cols)] for y in range(rows)]
        initial_config = state
        return jsonify(state)

    pattern = np.array(config[key])
    state = np.zeros((rows,cols))

    i = int(state.shape[0]/2 - pattern.shape[0])
    j = int(state.shape[1]/2 - pattern.shape[1])

    state[i:i+pattern.shape[0],j:j+pattern.shape[1]] += pattern
    state = state.tolist()
    initial_config = state

    return jsonify(state)
        

@app.route("/start")
def counter():
    global initial_config
    state = initial_config
    def respond_to_client(state):
        while True:
            state = getNextState(state)
            time.sleep(1)
            _data = json.dumps({"state": state})
            yield f"data: {_data}\nevent: online\n\n"
    return Response(respond_to_client(state), mimetype='text/event-stream')

if __name__ == '__main__':
    app.run(debug=True)
