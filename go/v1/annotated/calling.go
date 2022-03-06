     1	package main
     2	
     3	import (
     4		"fmt"
     5	)
     6	
     7	type Struct struct {
     8		variable int
     9	}
    10	
    11	func (s *Struct) doReceiver() int {
    12		return s.variable
    13	}
    14	
    15	func function(f int32) int64 {
    16		return int64(f)
    17	}
    18	
    19	func main() {
    20		fmt.Printf("Hello, World: %v\n", function(57005))
    21	
    22		s := Struct{}
    23		s.variable = 48879
    24		result := s.doReceiver()
    25	
    26		fmt.Printf("result %d\n", result)
    27	}

000000000047f8a0 <main.main>:
  47f8a0:	4c 8d 64 24 d8       	lea    r12,[rsp-0x28]
  47f8a5:	4d 3b 66 10          	cmp    r12,QWORD PTR [r14+0x10]
  47f8a9:	0f 86 76 01 00 00    	jbe    47fa25 <main.main+0x185>
  47f8af:	48 81 ec a8 00 00 00 	sub    rsp,0xa8
  47f8b6:	48 89 ac 24 a0 00 00 	mov    QWORD PTR [rsp+0xa0],rbp
  47f8bd:	00 
  47f8be:	48 8d ac 24 a0 00 00 	lea    rbp,[rsp+0xa0]
  47f8c5:	00 
  47f8c6:	b8 ad de 00 00       	mov    eax,0xdead
  47f8cb:	e8 90 ff ff ff       	call   47f860 <main.function>
  47f8d0:	48 89 44 24 38       	mov    QWORD PTR [rsp+0x38],rax
  47f8d5:	44 0f 11 7c 24 60    	movups XMMWORD PTR [rsp+0x60],xmm15
  47f8db:	48 8d 4c 24 60       	lea    rcx,[rsp+0x60]
  47f8e0:	48 89 4c 24 58       	mov    QWORD PTR [rsp+0x58],rcx
  47f8e5:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  47f8ea:	e8 b1 9c f8 ff       	call   4095a0 <runtime.convT64>
  47f8ef:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
  47f8f4:	48 8b 4c 24 58       	mov    rcx,QWORD PTR [rsp+0x58]
  47f8f9:	84 01                	test   BYTE PTR [rcx],al
  47f8fb:	48 8d 15 1e 70 00 00 	lea    rdx,[rip+0x701e]        # 486920 <type.*+0x6920>
  47f902:	48 89 11             	mov    QWORD PTR [rcx],rdx
  47f905:	48 8d 79 08          	lea    rdi,[rcx+0x8]
  47f909:	83 3d 70 66 0d 00 00 	cmp    DWORD PTR [rip+0xd6670],0x0        # 555f80 <runtime.writeBarrier>
  47f910:	74 02                	je     47f914 <main.main+0x74>
  47f912:	eb 06                	jmp    47f91a <main.main+0x7a>
  47f914:	48 89 41 08          	mov    QWORD PTR [rcx+0x8],rax
  47f918:	eb 08                	jmp    47f922 <main.main+0x82>
  47f91a:	e8 a1 b2 fd ff       	call   45abc0 <runtime.gcWriteBarrier>
  47f91f:	90                   	nop
  47f920:	eb 00                	jmp    47f922 <main.main+0x82>
  47f922:	48 8b 4c 24 58       	mov    rcx,QWORD PTR [rsp+0x58]
  47f927:	84 01                	test   BYTE PTR [rcx],al
  47f929:	eb 00                	jmp    47f92b <main.main+0x8b>
  47f92b:	48 89 8c 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rcx
  47f932:	00 
  47f933:	48 c7 84 24 90 00 00 	mov    QWORD PTR [rsp+0x90],0x1
  47f93a:	00 01 00 00 00 
  47f93f:	48 c7 84 24 98 00 00 	mov    QWORD PTR [rsp+0x98],0x1
  47f946:	00 01 00 00 00 
  47f94b:	48 8d 05 42 7b 01 00 	lea    rax,[rip+0x17b42]        # 497494 <go.string.*+0x1e54>
  47f952:	bb 11 00 00 00       	mov    ebx,0x11
  47f957:	bf 01 00 00 00       	mov    edi,0x1
  47f95c:	48 89 fe             	mov    rsi,rdi
  47f95f:	90                   	nop
  47f960:	e8 bb 96 ff ff       	call   479020 <fmt.Printf>
  47f965:	48 c7 44 24 28 00 00 	mov    QWORD PTR [rsp+0x28],0x0
  47f96c:	00 00 
  47f96e:	48 c7 44 24 28 ef be 	mov    QWORD PTR [rsp+0x28],0xbeef
  47f975:	00 00 
  47f977:	48 8d 44 24 28       	lea    rax,[rsp+0x28]
  47f97c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  47f980:	e8 9b fe ff ff       	call   47f820 <main.(*Struct).doReceiver>
	# rax holds the return value of the doReceiver method.
	# move the value of rax (see above) into memory -- ie, free up the register.
  47f985:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  47f98a:	44 0f 11 7c 24 60    	movups XMMWORD PTR [rsp+0x60],xmm15
  47f990:	48 8d 54 24 60       	lea    rdx,[rsp+0x60]
  47f995:	48 89 54 24 48       	mov    QWORD PTR [rsp+0x48],rdx
	# move the return value of the doReceiver method back into rax.
  47f99a:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
  47f99f:	90                   	nop
	# convT64 will convert its parameter (rax, ie the result of doReceiver)
	# into a pointer to that value.
  47f9a0:	e8 fb 9b f8 ff       	call   4095a0 <runtime.convT64>
	# rax is now a pointer to the value that we passed in -- the return value
	# of doReceiver
	# Store that into memory.
  47f9a5:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
	# The 8 bytes at rsp + 0x48 "obviously" contain a pointer
	# to some memory. Load the value at that address into rdx.
  47f9aa:	48 8b 54 24 48       	mov    rdx,QWORD PTR [rsp+0x48]
  47f9af:	84 02                	test   BYTE PTR [rdx],al
	# Store a "type" identifier into the register r8
  47f9b1:	4c 8d 05 a8 6e 00 00 	lea    r8,[rip+0x6ea8]        # 486860 <type.*+0x6860>
	# Store that type identifier into the target of the pointer in rdx
  47f9b8:	4c 89 02             	mov    QWORD PTR [rdx],r8
	# Load the address 8 bytes *after* where we just wrote the type id.
  47f9bb:	48 8d 7a 08          	lea    rdi,[rdx+0x8]
	# If the value at that address is *not* 0, then we are going to call
	# a write barrier (which probably tells the GC that we have potentially
	# freed something which could now be GC'd)
  47f9bf:	83 3d ba 65 0d 00 00 	cmp    DWORD PTR [rip+0xd65ba],0x0        # 555f80 <runtime.writeBarrier>
  47f9c6:	74 02                	je     47f9ca <main.main+0x12a>
  47f9c8:	eb 06                	jmp    47f9d0 <main.main+0x130>
	# Now, we are going to put rax (remember, it holds a pointer to the result
	# of doReceiver) in the slot of memory immediately after the identifier
	# that we filled earlier.
	# Let's remember: rdx holds a pointer to something that holds a pointer
	# to the result of doReceiver -- at this point it's our golden ticket.
  47f9ca:	48 89 42 08          	mov    QWORD PTR [rdx+0x8],rax
  47f9ce:	eb 07                	jmp    47f9d7 <main.main+0x137>
  47f9d0:	e8 eb b1 fd ff       	call   45abc0 <runtime.gcWriteBarrier>
  47f9d5:	eb 00                	jmp    47f9d7 <main.main+0x137>
	# Ugh, we cannot forget that [rsp + 0x48] also has a pointer
	# to this magical thing that we have been constructing! 
  47f9d7:	48 8b 4c 24 48       	mov    rcx,QWORD PTR [rsp+0x48]
	# In other words, the value of the rdx register should be the same
	# as the value of the 8 bytes at [rsp + 0x48] when we are here.
	# Taken cumulatively, rcx should now be pointing to that magical
	# structure, too!
  47f9dc:	84 01                	test   BYTE PTR [rcx],al
  47f9de:	66 90                	xchg   ax,ax
  47f9e0:	eb 00                	jmp    47f9e2 <main.main+0x142>
  47f9e2:	48 89 4c 24 70       	mov    QWORD PTR [rsp+0x70],rcx
  47f9e7:	48 c7 44 24 78 01 00 	mov    QWORD PTR [rsp+0x78],0x1
  47f9ee:	00 00 
  47f9f0:	48 c7 84 24 80 00 00 	mov    QWORD PTR [rsp+0x80],0x1
  47f9f7:	00 01 00 00 00 
	# We are gearing up to call another function! Load the ... 
	# into the spot for the first parameter.
  47f9fc:	48 8d 05 73 6a 01 00 	lea    rax,[rip+0x16a73]        # 496476 <go.string.*+0xe36>
	# We are putting 0xa into the second parameter? I wonder why ...
	# 0xa = 10d = length("result: %d\n") ? Yes, without the newline?
  47fa03:	bb 0a 00 00 00       	mov    ebx,0xa
	# Notice that we are not putting anything in rcx and skipping over it ...
	# I wonder why? (see above)
	# Putting something into the fourth parameter? That's a 1. I wonder
	# what that means?
  47fa08:	bf 01 00 00 00       	mov    edi,0x1
	# We are also putting a 1 in the fifth parameter? That's a 1. Hmm.
	# The mystery is answered: variadic parameter lists are implemented
	# as a sequence of three things: 
	# 1. A pointer to the slice backing the list of arguments.
	# 2. The length of the slice ...
	# 3. The capacity of the slice ...
	# We have a slice with a single element, so therefore we have a slice
	# with length/capacity of 1.
  47fa0d:	48 89 fe             	mov    rsi,rdi
  47fa10:	e8 0b 96 ff ff       	call   479020 <fmt.Printf>
  47fa15:	48 8b ac 24 a0 00 00 	mov    rbp,QWORD PTR [rsp+0xa0]
  47fa1c:	00 
  47fa1d:	48 81 c4 a8 00 00 00 	add    rsp,0xa8
  47fa24:	c3                   	ret    
  47fa25:	e8 d6 91 fd ff       	call   458c00 <runtime.morestack_noctxt.abi0>
  47fa2a:	e9 71 fe ff ff       	jmp    47f8a0 <main.main>
