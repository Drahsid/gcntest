# GCN Test
Sample program showing how to use a gcn controller on n64

## Building
You must create a `lib` folder and populate it with the following files:
- boot.6102
- gspF3DEX2.fifo_o32.o
- rspboot_o32.o

Furthermore, you must compile libultra, and place the outputs as
- libultra_d_o32.a
- libultra_rom_o32.a

Then simply run `make`.
