#----------------------------------------------------------
# make_info.py
# date: 07.07.2022
#----------------------------------------------------------
Import("env")
import shutil
import configparser
import os

def _get_board_f_flash(env):
    frequency = env.subst("$BOARD_F_FLASH")
    frequency = str(frequency).replace("L", "")
    return str(int(int(frequency) / 1000000)) + "m"

def createInf(source, target, env):
  print("\n==> Creating project.ini\n")

  my_flags = env.ParseFlags(env['BUILD_FLAGS'])
  defines = { k:v for (k, v) in my_flags.get("CPPDEFINES") }

  config = configparser.ConfigParser()  
  config.add_section('project')
  config.set('project', 'name',     defines.get("PROG_NAME"))
  config.set('project', 'mcu',      env.get("BOARD_MCU"))
  config.set('project', 'syscode',  defines.get("PROG_SYSCODE"))
  config.set('project', 'sysid',    defines.get("PROG_SYSID"))
  config.set('project', 'version',  defines.get("PROG_VERSION"))
  config.set('project', 'baud',     defines.get("UPDATE_BAUD"))
  ndef = env.get("PROJECT_BUILD_DIR") + "\\" + env.get("PIOENV")
  config.set('project', 'firmware',  ndef + '\\firmware.bin')
  xtra = env.get("FLASH_EXTRA_IMAGES")
  for x in xtra:
#    print(x)
    if((x[0] == '0x0000') or (x[0] == '0x1000')):
      filename = os.path.basename(env.subst(x[1]))
      shutil.copy(env.subst(x[1]), ndef + '\\' + filename)
      config.set('project', 'bootloader', ndef + '\\' + filename)
    if x[0] == '0x8000':
      config.set('project', 'partitions', x[1])
    if x[0] == '0xe000':
      filename = os.path.basename(env.subst(x[1]))
      shutil.copy(env.subst(x[1]), ndef + '\\' + filename)
      config.set('project', 'appdata', ndef + '\\' + filename)

  with open("project.ini", "w") as cfgfile:
    config.write(cfgfile)

#  print(env.Dump())
#  print(env.get("__get_board_f_flash(__env__)"))
#  print('K:\\PlatformIO\\.platformio\\packages\\framework-arduinoespressif32\\tools\\sdk\\bin\\bootloader_${BOARD_FLASH_MODE}_${__get_board_f_flash(__env__)}.bin')
#  print(env.get("FLASH_EXTRA_IMAGES")[0][1])
#  print(env.get("FLASH_EXTRA_IMAGES")[1])
#  print(env.get("FLASH_EXTRA_IMAGES")[2])

env.AddPostAction("checkprogsize", createInf)


