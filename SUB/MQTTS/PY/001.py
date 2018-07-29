


import paho.mqtt.client as paho

def on_message(clnt, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

mqttc = paho.Client()
#mqttc.on_message = on_message
mqttc.tls_set("fff.crt") # http://test.mosquitto.org/ssl/mosquitto.org.crt


#mqttc.connect("test.mosquitto.org", 8883)
mqttc.connect("iot.eclipse.org", 8883)
mqttc.publish("dach_dach/x", "Hello, World!ddd")

#mqttc.subscribe("bbc/#")
#mqttc.loop_forever()
mqttc.loop(2)
exit()




import paho.mqtt.client as mqtt

mqttc = mqtt.Client("python_pub")
mqttc.connect("iot.eclipse.org", 8883)
mqttc.publish("dach_dach/x", "Hello, World!ddd")
mqttc.loop(2)
exit()







import paho.mqtt.client as mqttClient
import time
import json
import ssl

def on_connect(client, userdata, flags, rc):
 
    if rc == 0:
 
        print("Connected to broker")
 
        global Connected                #Use global variable
        Connected = True                #Signal connection 
 
    else:
 
        print("Connection failed")

def on_publish(client, userdata, result):

	print "Published!"


Connected = False
broker_address= "industrial.api.ubidots.com"
port = 8883
user = "YOUR-UBIDOTS-TOKEN"
password = ""
topic = "/v1.6/devices/mqtt"

client = mqttClient.Client()
client.username_pw_set(user, password=password)
client.on_connect = on_connect
client.on_publish = on_publish

client.tls_insecure_set(False)
client.tls_set(ca_certs="industrial.pem", certfile=None, keyfile=None, cert_reqs=ssl.CERT_REQUIRED, tls_version=ssl.PROTOCOL_TLSv1_2, ciphers=None)
client.connect(broker_address, port=port)
client.loop_start()

while Connected != True:    #Wait for connection
    print "Connecting..."
    time.sleep(1)
 
try:
    while True:
        payload = json.dumps({"tls_publish_test":20})
        print payload
        client.publish(topic, payload)
        time.sleep(10)
 
except KeyboardInterrupt:
 
    client.disconnect()
    client.loop_stop()
    
    
exit()





















import paho.mqtt.client as mqtt

mqttc = mqtt.Client("python_pub")
mqttc.connect("iot.eclipse.org", 8883)
mqttc.publish("dach_dach/x", "Hello, World!ddd")
mqttc.loop(2)
exit()




import paho.mqtt.client as paho

def on_message(clnt, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

mqttc = paho.Client()
mqttc.on_message = on_message
mqttc.tls_set("mosquitto.org.crt") # http://test.mosquitto.org/ssl/mosquitto.org.crt
mqttc.connect("test.mosquitto.org", 8883)
mqttc.subscribe("bbc/#")
mqttc.loop_forever()
exit()