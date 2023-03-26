        section .data
twelve: dq 12.0
reg_xmm0:db "xmm0", 0
fmtmc:  db "Memory contents: ", 0
fmtc:   db "0x%02hhx ", 0
fmtnl:  db 10, 0
fmtf:   db "%-15s: %f", 10, 0

        section .text
				default rel
        extern printf
        global main
main: 
        push rbp

				mov rdi, fmtmc
        call printf wrt ..plt     ; call printf

				mov rdi, fmtc
				mov sil, [twelve]
        call printf wrt ..plt     ; call printf

				mov rdi, fmtc
				mov sil, [twelve + 1]
        call printf wrt ..plt     ; call printf

				mov rdi, fmtc
				mov sil, [twelve + 2]
        call printf wrt ..plt     ; call printf

				mov rdi, fmtc
				mov sil, [twelve + 3]
        call printf wrt ..plt     ; call printf


				mov rdi, fmtc
				mov sil, [twelve + 4]
        call printf wrt ..plt     ; call printf


				mov rdi, fmtc
				mov sil, [twelve + 5]
        call printf wrt ..plt     ; call printf


				mov rdi, fmtc
				mov sil, [twelve + 6]
        call printf wrt ..plt     ; call printf

				mov rdi, fmtc
				mov sil, [twelve + 7]
        call printf wrt ..plt     ; call printf

				mov rdi, fmtnl
        call printf wrt ..plt     ; call printf

				mov rdi, fmtf
				movsd xmm0, [twelve]

				mov rsi, reg_xmm0
        call printf wrt ..plt     ; call printf

				pop rbp
				ret
