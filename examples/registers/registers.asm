        section .data
reg_rbx:db "rbx", 0
reg_ebx:db "ebx", 0
reg_bx: db " bx", 0
reg_bh: db " bh", 0
reg_bl: db " bl", 0
fmt:    db "%s: %16lx", 10, 0
raw:    db 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88

        section .text
				default rel
        extern printf
        global main
main: 
        push rbp
        mov rbx, [raw]

				mov rdi, fmt
				mov rsi, reg_rbx
				xor rdx, rdx
				mov rdx, rbx
        call printf wrt ..plt     ; call printf

				mov rdi, fmt
				mov rsi, reg_ebx
				xor rdx, rdx
				mov edx, ebx
        call printf wrt ..plt     ; call printf

				mov rdi, fmt
				mov rsi, reg_bx
				xor rdx, rdx
				mov dx, bx
        call printf wrt ..plt     ; call printf

				mov rdi, fmt
				mov rsi, reg_bh
				mov dh, bh
        call printf wrt ..plt     ; call printf

				mov rdi, fmt
				mov rsi, reg_bl
				xor rdx, rdx
				mov dl, bl
        call printf wrt ..plt     ; call printf

				pop rbp
				ret
