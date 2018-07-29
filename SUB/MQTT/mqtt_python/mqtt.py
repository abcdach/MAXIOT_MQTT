#!/usr/bin/env python
# -*- coding: utf-8 -*-
import paho.mqtt.client as mqtt
import time, threading, ssl

receivedMessages = []

def on_message(client, userdata, message):
  print("Received operation " + str(message.payload))
  if (message.payload.startswith("510")):
     print("Simulating device restart...")
     publish("s/us", "501,c8y_Restart");
     print("...restarting...")
     time.sleep(1)
     publish("s/us", "503,c8y_Restart");
     print("...done...")

def sendMeasurements():
  try:
    print("Sending temperature measurement")
    publish("dach_dach/x", "211,25");
    thread = threading.Timer(3, sendMeasurements)
    thread.daemon=True
    thread.start()
    while True: time.sleep(100)
  except (KeyboardInterrupt, SystemExit):
    print 'Received keyboard interrupt, quitting ...'


def publish(topic, message, waitForAck = False):
  mid = client.publish(topic, message, 2)[1]
  if (waitForAck):
    while mid not in receivedMessages:
      time.sleep(0.25)

def on_publish(client, userdata, mid):
  receivedMessages.append(mid)

client = mqtt.Client(client_id="<<clientId>>")
client.username_pw_set("<<tenant>>/<<username>>", "<<password>>")
client.on_message = on_message
client.on_publish = on_publish

client.connect("iot.eclipse.org", 1883)
client.loop_start()
#publish("dach_dach/x", "100,Python MQTT,c8y_MQTTDevice", True)
#publish("s/us", "110,S123456789,MQTT test model,Rev0.1")
client.subscribe("dach_dach/x")
publish("dach_dach/x", "211,25");
#sendMeasurements()






