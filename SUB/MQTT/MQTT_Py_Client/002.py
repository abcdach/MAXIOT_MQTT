import paho.mqtt.client as mqtt

mqttc = mqtt.Client("556/My device")
mqttc.connect("127.0.0.1", 3004, 60)
mqttc.publish("0/temperatura", "25.5")
mqttc.loop(2)