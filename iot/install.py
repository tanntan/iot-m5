import sys
import os
from pathlib import Path
import shutil
import glob
import time

DIR = Path(__file__).parent.resolve()
proDir = Path().parent.resolve()

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
       

def deletWorkingSpace( srcPath ):
    working = os.path.join(proDir, srcPath)
    exceptBin = ["firmware.bin", "firmware.elf", "spiffs.bin"]
    l = 0
    i = 0
    for path, subdirs, files in os.walk(str(working)):
        l += 1

    printProgressBar(0, l, prefix = 'Progress:', suffix = 'Complete', length = 50)
    for path, subdirs, files in os.walk(str(working)):
        i+=1
        for name in files:
            if name not in exceptBin:
                os.remove(os.path.join(path, name))
                time.sleep(0.05)
        printProgressBar(i + 1, l, prefix = 'Progress:', suffix = os.path.join(proDir, srcPath), length = 50)
        
def createHeader(val):
    val = val.split("\n")
    stringVal = '#define VERSION        "'+val[0]+'"'
    return stringVal

def getVersion():
    f = open("version", "r")
    readVal = f.readline()
    f.close()
    h = open("iot/libs/version.h", "w")
    h.write(createHeader(readVal))
    h.close()


def main():
    if len(sys.argv) < 2:
        print("")

    elif sys.argv[1] == "init":
        command = "pip3 install platformio -t "+str(DIR)    +"/.platformio/"
        os.system("pip3 install pyelftools -t "+str(DIR))
        os.system(command)
    else:
        if sys.argv[1] == "build":
            if len(sys.argv) <= 3:
                print("Please define Src directory")

            else:
                if len(sys.argv) != 4:
                    print("Please Put command")

                else:
                    if sys.argv[2] == "--release":
                        cmdbuild = str(DIR)+"/pio run -d " + sys.argv[3] +" -e release && /" +  str(DIR)+"/pio run --target buildfs -d" + sys.argv[3] + " -e release"
                        os.system(cmdbuild)
                        print("=====================Start Clean==============")
                        clearUnUseWorkSpace()
                        deletWorkingSpace(sys.argv[3])
                        print("=====================Finish==============")
                        
                    elif sys.argv[2] == "--debug":
                        cmdbuild = str(DIR)+"/pio run -d " + sys.argv[3] +" -e debug && /" +  str(DIR)+"/pio run --target buildfs -d" + sys.argv[3] + " -e debug"
                        os.system(cmdbuild)
                    else:
                        print("No function")
        else:
            print("not build")



if __name__ == '__main__':
    
    main()
