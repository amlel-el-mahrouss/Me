OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)
OUTPUT(LumiaRT.app)

. = 1M;

SECTIONS
{
	.text : {
		PROVIDE(kBeginText = .);
		*(.text);
		PROVIDE(kEndText = .);
	}

	.data : {
		PROVIDE(kBeginData = .);
		*(.data);
		PROVIDE(kEndData = .);
	}

	.bss : {
		PROVIDE(kBeginBss = .);
		*(.bss);
		PROVIDE(kBeginBss = .);
	}

	PROVIDE(kMemoryStart = 1M);

	PROVIDE(kStackStart = __end_bss);
	PROVIDE(kStackEnd = kStackStart + 0x8000);

	PROVIDE(kMemoryEnd = 1M + 512M);

	PROVIDE(kPagePtr = .);

}