typedef struct
{
  0 unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
  15 Elf64_Half	e_type;			/* Object file type */
  17 Elf64_Half	e_machine;		/* Architecture */
  19 Elf64_Word	e_version;		/* Object file version */
  23 Elf64_Addr	e_entry;		/* Entry point virtual address */
  31 Elf64_Off	e_phoff;		/* Program header table file offset */
  Elf64_Off	e_shoff;		/* Section header table file offset */
  Elf64_Word	e_flags;		/* Processor-specific flags */
  Elf64_Half	e_ehsize;		/* ELF header size in bytes */
  Elf64_Half	e_phentsize;		/* Program header table entry size */
  Elf64_Half	e_phnum;		/* Program header table entry count */
  Elf64_Half	e_shentsize;		/* Section header table entry size */
  Elf64_Half	e_shnum;		/* Section header table entry count */
  Elf64_Half	e_shstrndx;		/* Section header string table index */
} Elf64_Ehdr;
