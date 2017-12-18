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

	.text ALIGN (0x1000) : {
		kernel_comment_start = .;
		*(.comment)
		kernel_comment_end = .;

		kernel_debug_info_start = .;
		*(.debug_info)
		kernel_debug_info_end = .;

		kernel_debug_str_start = .;
		*(.debug_str)
		kernel_debug_str_end = .;

		kernel_debug_abbrev_start = .;
		*(.debug_abbrev)
		kernel_debug_abbrev_end = .;

		kernel_debug_macinfo_start = .;
		*(.debug_macinfo)
		kernel_debug_macinfo_end = .;

		kernel_debug_pubnames_start = .;
		*(.debug_pubnames)
		kernel_debug_pubnames_end = .;

		kernel_debug_pubtypes_start = .;
		*(.debug_pubtypes)
		kernel_debug_pubtypes_end = .;

		kernel_debug_frame_start = .;
		*(.debug_frame)
		kernel_debug_frame_end = .;

		kernel_debug_line_start = .;
		*(.debug_line)
		kernel_debug_line_end = .;

		kernel_debug_loc_start = .;
		*(.debug_loc)
		kernel_debug_loc_end = .;
	}
}

