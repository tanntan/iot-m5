import sys
import os
from pathlib import Path
import shutil
import glob
import time

Import("env")
def txtFilter(txt):
    newVal = txt[0].split("\n")
    return newVal[0]

def getVersion():
    f = open("../../version", "r")
    value = f.readlines()
    return txtFilter(value)

env.Replace(PROGNAME="firmware_%s" % getVersion())