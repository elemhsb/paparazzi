target extended 127.0.0.1:4242
file ~/work/gits/warmers/forschung/elemhsb-paparazzi/var/aircrafts/HB_OlimexProbe/ap/ap.elf
tbreak main
tbreak chibios_logInit
jump ResetHandler
