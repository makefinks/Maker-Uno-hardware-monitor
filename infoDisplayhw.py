import time
import serial
import wmi

global w
w = wmi.WMI(namespace="root/OpenHardwareMonitor")

def updateHwInfo():
    hw_infos = w.sensor()
    global cpuTemp
    global gpuTemp
    global cpuUsage
    global gpuUsage
    global ramUsage
    global powerDraw
    global powerDrawM
    global gpuFan
    global cpuFan

    cpuTemp = ""
    gpuTemp = ""
    cpuUsage = ""
    gpuUsage = ""
    ramUsage = ""
    powerDraw = ""
    powerDrawM = ""
    gpuFan = ""
    cpuFan = ""
    
    for sensor in hw_infos:
        if sensor.SensorType == u"Temperature":
            if sensor.Name == u"CPU CCD #1":
                cpuTemp = "%d" % sensor.Value
            elif sensor.Name == u"GPU Core":
                gpuTemp = "%d" % sensor.Value
        if sensor.SensorType == u"Load":
           if sensor.Name == u"CPU Total":
               if(sensor.Value < 10):
                   cpuUsage = " %d" % round(sensor.Value)
               elif(sensor.Value == 100):
                   cpuUsage = "99"
               else:
                   cpuUsage = "%d" % round(sensor.Value)
           if sensor.Name == u"GPU Core":
               if(sensor.Value < 10):
                   gpuUsage = " %d" % round(sensor.Value)
               elif(sensor.Value == 100):
                   gpuUsage = "99"
               else:
                   gpuUsage = "%d" % round(sensor.Value)
                  

        if sensor.SensorType == u"Power":
           if sensor.Name == u"CPU Package":
                powerDrawM = "%d" % sensor.Max
                powerDraw = "%d" % sensor.Value
           elif sensor.Name == u"GPU Power":
                powerDrawMT = int(powerDrawM)
                powerDrawT = int(powerDraw)
                if(sensor.Max + powerDrawMT < 100):
                    powerDrawM = " %d" % int(sensor.Max + powerDrawMT)
                elif(sensor.Max + powerDrawMT < 10):
                    powerDrawM = "  %d" % int(sensor.Max + powerDrawMT)
                else:
                    powerDrawM = "%d" % int(sensor.Max + powerDrawMT)
                if(powerDrawT + sensor.Value < 100):
                    powerDraw = " %d" % int(sensor.Value + powerDrawT)
                elif(powerDrawT + sensor.Value < 10):
                    powerDraw = "  %d" % int(sensor.Value + powerDrawT)
                else:
                    powerDraw = "%d" % int(sensor.Value + powerDrawT)
             
            
        if sensor.SensorType == u"Data":
            if(sensor.Name == u"Used Memory"):
                if(sensor.Value < 10):
                    ramUsage = " %d" % sensor.Value
                else:
                    ramUsage = "%d" % sensor.Value

        if sensor.SensorType == u"Control":
            if(sensor.Name == u"GPU Fan"):
                if(sensor.Value == 100):
                    gpuFan = "%d" % sensor.Value
                elif(sensor.Value < 100 and sensor.Value>= 10):
                    gpuFan = " %d" % sensor.Value
                else:
                    gpuFan = "  %d" % sensor.Value
        
        if sensor.SensorType == u"Fan":
            if(sensor.Name == u"Fan #2"):
                if(sensor.Value < 100):
                    cpuFan = "  %d" % sensor.Value
                elif(sensor.Value >= 100 and sensor.Value < 1000):
                    cpuFan = " %d" % sensor.Value
                elif(sensor.Value >= 1000):
                    cpuFan = "%d" % sensor.Value


arduino = serial.Serial("COM3", 9600, timeout=.7)

while True:

    updateHwInfo()
    arduino.write(cpuTemp.encode())
    arduino.write(gpuTemp.encode())
    arduino.write(cpuUsage.encode())
    arduino.write(gpuUsage.encode())
    arduino.write(ramUsage.encode())
    arduino.write(powerDraw.encode())
    arduino.write(powerDrawM.encode())
    arduino.write(gpuFan.encode())
    arduino.write(cpuFan.encode())
    print("CPU temp: " +cpuTemp)
    print("GPU temp: " +gpuTemp)
    print("CPU usage: " + cpuUsage)
    print("GPU usage: " + gpuUsage)
    print("RAM usage: " + ramUsage)
    print("Power Draw: " + powerDraw)
    print("power Draw Max: " + powerDrawM)
    print("Gpu Fan Speed: " + gpuFan)
    print("Cpu Fan Speed: " + cpuFan)
    
    time.sleep(2)
