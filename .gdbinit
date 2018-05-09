set target-async on
set confirm off
set history save
set mem inaccessible-by-default off
target extended-remote /dev/ttyACM0
mon swdp_scan
att 1
load ./build/src/crimea_stm32.elf
file ./build/src/crimea_stm32.elf
start
