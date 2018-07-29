#!/usr/bin/python
import subprocess, sys
## command to run - tcp only ##
#cmd = "/usr/sbin/netstat -p tcp -f inet"

cmd = "/home/maxiot/TEMP_MQTT_FileConfig/SUB/POPEN/Test_Stream/test ";

 
## run it ##
p = subprocess.Popen(cmd, shell=True, stderr=subprocess.PIPE)
 
## But do not wait till netstat finish, start displaying output immediately ##
while True:
    out = p.stderr.read(1)
    if out == '' and p.poll() != None:
        break
    if out != '':
        sys.stdout.write(out)
        sys.stdout.flush()