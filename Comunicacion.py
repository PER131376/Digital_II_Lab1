# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Selvin E. Peralta Cifuentes

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
#  
import serial
import time
from Adafruit_IO import Client, RequestError, Feed
puerto = serial.Serial('COM2',9600)

ADAFRUIT_IO_KEY = "aio_IWFP39W4gXvDB9LAz38Ql0jnvsVD"
ADAFRUIT_IO_USERNAME = "Selvin55"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Digital Feed
#digital_feed = aio.feeds('aceleracion')
#aio.send_data(digital_feed.key, 100)
#digital_data = aio.receive(digital_feed.key)
#print(f'Potencia: {digital_data.value}')

#Analog Feed
while 1:
    #aio.send_data(analog_feed.key,22)
    ValorPORTD_feed = aio.feeds('aceleracion')
    ValorPORTD_data = aio.receive('aceleracion').value
    puerto.write(chr(int(ValorPORTD_data)).encode())
    time.sleep(2)

    
