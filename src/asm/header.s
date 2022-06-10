.section .data

.byte  0x80, 0x37, 0x12, 0x40   /* PI BSD Domain 1 register */
.word  0x0000000F               /* Clockrate setting*/
.word  entrypoint               /* Entrypoint */
.word  0x0000144E               /* SDK Revision */
.word  0x00000000               /* Checksum 1 */
.word  0x00000000               /* Checksum 2 */
.word  0x00000000               /* Unknown */
.word  0x00000000               /* Unknown */
.ascii "GCNTEST             "   /* Internal ROM name (Max 20 characters) */
.word  0x00000000               /* Unknown */
.word  0x0000004E               /* Cartridge Type (N) */
.ascii "GC"                     /* Cartridge ID (SM) */
.ascii "E"                      /* Region (E) */
.byte  0x00                     /* Version */
