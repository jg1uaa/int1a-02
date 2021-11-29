// SPDX-License-Identifier: WTFPL
// apt-get install bcc
// bcc -ansi -Md -O int1a-02.c -o int1a-02.com

#include <stdio.h>

int int1a(unsigned int ah, unsigned short *cx, unsigned short *dx)
{
#asm
	push	bp
	mov	bp, sp

	mov	ax, [bp + 4]
	int	0x1a

	pushf	

	mov	bx, [bp + 6]
	mov	[bx], cx
	mov	bx, [bp + 8]
	mov	[bx], dx

	pop	ax
	and	ax, #0x0001	; carry flag

	pop	bp
#endasm
}

int main(int argc, char *argv[])
{
	/* "static" means variables are allocated on data segment */
	static unsigned short ax, cx, dx;

	ax = int1a(0x0200, &cx, &dx);
	printf("CF=%04x  CX=%04x DX=%04x\n", ax, cx, dx);
	
	ax = int1a(0x0400, &cx, &dx);
	printf("CF=%04x  CX=%04x DX=%04x\n", ax, cx, dx);

	return 0;
}
