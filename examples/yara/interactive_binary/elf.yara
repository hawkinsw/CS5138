rule ElfBinary
{
	meta:
		file_type = "Binary"
		interactive = "No"

	strings:
		$elf = { 7f 45 4c 46 }
	condition:
		$elf
}

rule Interactive
{
	meta:
		file_type = "Binary"
		interactive = "Yes"
	strings:
		$readline = { 6c 69 62 72 65 61 64 6c 69 6e 65 2e 73 6f 2e 38 }
	condition:
			ElfBinary and $readline
}
