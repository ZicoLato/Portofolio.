from flask import Flask, request, render_template
import pickle

app = Flask(__name__)

model_file = open('model.pkl', 'rb')
model = pickle.load(model_file, encoding='bytes')

@app.route('/')
def index():
    return render_template('index.html', insurance_cost=0)

@app.route('/predict', methods=['POST'])
def predict():
    '''
    Predict the insurance cost based on user inputs
    and render the result to the html page
    '''
    BatteryPower, Blue, ClockSpeed, DualSim, Fc, FourG, IntMemory, MDep, MobileWt, NCores, Pc, PxHeight, PxWidth, Ram, ScH, ScW, TalkTime, ThreeG, TouchScreen, Wifi= [x for x in request.form.values()]

    data = []

    data.append(float(BatteryPower))
    data.append(float(Blue))
    data.append(float(ClockSpeed))
    data.append(float(DualSim))
    data.append(float(Fc))
    data.append(float(FourG))
    data.append(float(IntMemory))
    data.append(float(MDep))
    data.append(float(MobileWt))
    data.append(float(NCores))
    data.append(float(Pc))
    data.append(float(PxHeight))
    data.append(float(PxWidth))
    data.append(float(Ram))
    data.append(float(ScH))
    data.append(float(ScW))
    data.append(float(TalkTime))
    data.append(float(ThreeG))
    data.append(float(TouchScreen))
    data.append(float(Wifi))


    prediction = model.predict([data])
    if prediction==1 :
        output = "Harga Standar"
    elif prediction==2:
        output = "Harga Mahal"
    elif prediction==3:
        output = "Harga Sangat Mahal"
    else:
        output = "Harga Murah"

    return render_template('index.html', prediction=output, BatteryPower=BatteryPower, Blue=Blue, ClockSpeed=ClockSpeed, DualSim=DualSim, Fc=Fc, FourG=FourG, IntMemory=IntMemory, MDep=MDep, MobileWt=MobileWt, NCores=NCores, Pc=Pc, PxHeight=PxHeight, PxWidth=PxWidth, Ram=Ram, ScH=ScH, ScW=ScW, TalkTime=TalkTime, ThreeG=ThreeG, TouchScreen=TouchScreen, Wifi=Wifi)


if __name__ == '__main__':
    app.run(debug=True)
