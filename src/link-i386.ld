ENTRY(_start)

SECTIONS {
	. = 0x100000;
	kernel_start = .;

	.debug_info : {
		kernel_debug_info_start = .;
		*(.debug_info)
		kernel_debug_info_end = .;
	}

	.text : ALIGN (0x1000) {
		kernel_code_start = .;
		*(.mboot)
		*(.text)
		kernel_code_end = .;
	}

	.rodata ALIGN (0x1000) : {
		kernel_rodata_start = .;
		*(.rodata)
		kernel_rodata_end = .;
	}

	.data ALIGN (0x1000) : {
		kernel_data_start = .;
		*(.data)
		kernel_data_end = .;
	}

	.bss ALIGN (0x1000) : {
		kernel_bss_start = .;
		*(COMMON)
		*(.bss)
		kernel_bss_end = .;
	}

	kernel_end = .;
}

