from pathlib import Path
import os
import time
import sys
import shutil
import glob

Import("env", "projenv")

def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print(f'\r{prefix} |{bar}| {percent}% {suffix}', end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()

def toBeClean():
    for ex in ext:
        for f in Path(str(proDir)+'/temp').glob(ex):
            try:
                print(f)
                f.unlink()
            except OSError as e:
                print("Error: %s : %s" % (f, e.strerror))

def clearUnUseWorkSpace():
    i = 0
    l = 0
    for path, subdirs, files in os.walk(str(proDir)+'/apps'):
        l += 1

    #printProgressBar(0, l, prefix = 'Progress:', suffix = 'Complete', length = 50)
    for path, subdirs, files in os.walk(str(proDir)+'/apps'):
        i+=1
        for name in files:
            os.remove(os.path.join(path, name))
            time.sleep(0.1)
        
        printProgressBar(i + 1, l, prefix = 'Progress:', suffix = os.path.join(proDir), length = 50)
       

def deletWorkingSpace():
    #os.chdir("../..")
    folders = ["./apps", "./iot","./bin", "./docs", "./packages", "./scripts"]
    exceptBin = ["firmware.bin", "firmware.elf", "spiffs.bin"]
    l = 0
    i = 0

    for folder in folders:
        for root in os.walk(os.path.join("../..", folder), topdown=False):
            l += 1
        printProgressBar(0, l, prefix = 'Progress:', suffix = 'Complete', length = 50)
        for root, dirs, files in os.walk(os.path.join("../..", folder), topdown=False):
            for fileName in files:
                i += 1
                os.remove(os.path.join(root, fileName))
                time.sleep(0.02)
                printProgressBar(i + 1, l, prefix = 'Progress:', suffix = os.path.join(root, fileName), length = 50)
    
def after_upload(source, target, env):
    deletWorkingSpace()

#print(env.Dump)
env.AddPostAction("$PROGPATH", after_upload)



