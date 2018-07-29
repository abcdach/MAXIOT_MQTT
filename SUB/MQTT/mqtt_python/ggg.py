import paho.mqtt.client as mqtt

mqttc = mqtt.Client("python_pub")
mqttc.connect("iot.eclipse.org", 1883)
mqttc.publish("dach_dach/x", "Hello, World!")
mqttc.loop(2)



