## The Search Is On

__getmainargs

### Overall Structure

Talk about virtual addressing first!

### IMAGE_DOS_HEADER
```
typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    LONG   e_lfanew;                    // File address of new exe header
```

this points us to 0x00000c0 where we expect to see a IMAGE_NT_HEADER. Let's follow to that address.

### IMAGE_NT_HEADER

Magic: 0x50450000


`#define IMAGE_NT_SIGNATURE                  0x50450000  // PE00`

```
typedef struct _IMAGE_NT_HEADERS64 {
    DWORD Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;
```

So, at 0x..0c we should see the first four bytes match the IMAGE_NT_SIGNATURE. Let's check:

`000000c0  50 45 00 00 4c 01 04 00  31 90 ae 49 00 00 00 00  |PE..L...1..I....|`

Voila! So, we are on the right track! Now, let's skip ahead by sizeof(IMAGE_FILE_HEADER) where we should find an embedded IMAGE_OPTIONAL_HEADER64. The sizeof(IMAGE_FILE_HEADER) is 20 bytes  So, the OptionalHeader should start at 0x...c0 + 18 = 0x...d8

### IMAGE_FILE_HEADER

```
typedef struct _IMAGE_FILE_HEADER {
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
```

### IMAGE_OPTIONAL_HEADER

Magic: `0x10b`

`#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b`

`000000d0  00 00 00 00 e0 00 03 01  0b 01 09 00 00 26 00 00 |.............&..|`

Wohoo, it matches!!

The "first" fields are 96 bytes long (0x60, that is), so the array of directory data structures should begin at

0xd8 + 0x60 = 0x138


```
typedef struct _IMAGE_OPTIONAL_HEADER {
    //
    // Standard fields.
    //

    WORD    Magic; 2
    BYTE    MajorLinkerVersion; 3
    BYTE    MinorLinkerVersion; 4
    DWORD   SizeOfCode; 8
    DWORD   SizeOfInitializedData; 12
    DWORD   SizeOfUninitializedData; 16
    DWORD   AddressOfEntryPoint; 20
    DWORD   BaseOfCode; 24
    DWORD   BaseOfData; 28

    //
    // NT additional fields.
    //

    DWORD   ImageBase; 32
    DWORD   SectionAlignment; 36
    DWORD   FileAlignment; 40
    WORD    MajorOperatingSystemVersion; 42
    WORD    MinorOperatingSystemVersion; 44
    WORD    MajorImageVersion; 46
    WORD    MinorImageVersion; 48
    WORD    MajorSubsystemVersion; 50
    WORD    MinorSubsystemVersion; 52
    DWORD   Win32VersionValue; 56
    DWORD   SizeOfImage; 60
    DWORD   SizeOfHeaders; 64
    DWORD   CheckSum; 68
    WORD    Subsystem; 70
    WORD    DllCharacteristics; 72
    DWORD   SizeOfStackReserve; 76
    DWORD   SizeOfStackCommit; 80
    DWORD   SizeOfHeapReserve; 84
    DWORD   SizeOfHeapCommit; 88
    DWORD   LoaderFlags; 92
    DWORD   NumberOfRvaAndSizes; 96
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;
```

### Data Directories
```
typedef struct _IMAGE_DATA_DIRECTORY {
    DWORD   VirtualAddress;
    DWORD   Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;
```

Note: Each data directory is 8 bytes long. 
### IMAGE_DIRECTORY_ENTRY_IMPORT

It's the second in the list!
`#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory`

So, it should be 8 bytes after the first entry in the data directory entry (0x138). In other words, it should begin at 0x138 + 0x8 = 0x140. Let's see what bytes are there:

`00000140  4c 44 00 00 50 00 00 00  00 70 00 00 a0 03 00 00  |LD..P....p......|`

Looks interesting. Remember our endianness. This means that we should look for the import information to begin at 0x444c in the file. But, what exactly is that? 

Well, it's a virtual address relative to the baseimage. So, the first thing that we need to do is add `baseimage` (0x00400000)

that gives us 0x0040044c. 

Too bad that is a virtual address. To go further, we'll have to figure out what part of the raw file is actually there.

We can use pe-tree to find out that the .rdata section is mapped starting at 0x00404000. Okay, so we know that we are in the .rdata section and we are 0x44c from its beginning. But, where is that in the file on disk? Again, pe-tree will tell us that it is at 0x2a00. So, this should point to something on disk at 0x2a00 + 0x44c = 0x2e4c. But, what's there?

### IMAGE_IMPORT_DESCRIPTOR

`00002e40  00 00 00 00 78 53 40 00  28 44 40 00 dc 44 00 00  |....xS@.(D@..D..|`

```
typedef struct _IMAGE_IMPORT_DESCRIPTOR {
    union {
        DWORD   Characteristics;            // 0 for terminating null import descriptor
        DWORD   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    } DUMMYUNIONNAME;
    DWORD   TimeDateStamp;                  // 0 if not bound,
                                            // -1 if bound, and real date\time stamp
                                            //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                                            // O.W. date/time stamp of DLL bound to (Old BIND)

    DWORD   ForwarderChain;                 // -1 if no forwarders
    DWORD   Name;
    DWORD   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
} IMAGE_IMPORT_DESCRIPTOR;
```

And the `OriginalFirstThunk` points to 0x44dc. We add the `baseimage` to get 0x00400000 + 0x44dc = 0x4044dc and calculate that relative to the section mapped there in memory?

again, it's .rdata. So, we are 0x4dc into the .rdata and that means that we are 0x2a00 + 0x4dc = 0x2edc in the file. And what is there?

### IMAGE_THUNK_DATA32

`00002ed0  96 46 00 00 7c 47 00 00  00 00 00 00 04 46 00 00  |.F..|G.......F..|`

```
typedef struct _IMAGE_THUNK_DATA32 {
    union {
        DWORD ForwarderString;      // PBYTE 
        DWORD Function;             // PDWORD
        DWORD Ordinal;
        DWORD AddressOfData;        // PIMAGE_IMPORT_BY_NAME
    } u1;
} IMAGE_THUNK_DATA32;
```

So, we have a pointer to a PIMAGE_IMPORT_BY_NAME. Same relative addressing dance means that we are at 

0x4604 + 0x00400000 = 404604 - 404000 = 604 + 2a00 = 3004?  

### PIMAGE_IMPORT_BY_NAME

`00003000  64 6c 6e 00 58 00 5f 5f  67 65 74 6d 61 69 6e 61  |dln.X.__getmaina|`


```
typedef struct _IMAGE_IMPORT_BY_NAME {
    WORD    Hint;
    CHAR   Name[1];
} IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;
```


VOILA! We have the name of the function that we are going to import!!
