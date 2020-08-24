"""
Tests for the flail-test executable.
"""

from pathlib import Path
import subprocess
from textwrap import dedent


def test_flail():
    """Basic integration test for Flail."""
    path = Path(__file__).resolve().parent / 'flail-test'
    result = subprocess.run(str(path), capture_output=True, text=True, check=True)

    start, stack, end = result.stdout.split("\n\n\n")

    assert start == dedent("""\
        !!! Kernel panic !!!

        Flail test executable

        This kernel panic is intentional.""")

    lines = stack.split("\n")
    assert lines.pop(0) == "Stack dump:"
    assert lines.pop(0) == ""
    assert lines.pop(0).endswith(": 0x1")
    assert lines.pop(0).endswith(": 0x2")
    assert lines.pop(0).endswith(": 0xbadf00d")
    assert lines.pop(0).endswith(": 0xdeadbeef")
    assert lines.pop(0).endswith(": 0x9999999999999999")
    assert lines.pop(0).endswith(": 0x0")

    assert end == dedent("""\
        Kernel panic: This kernel panic is intentional.
         src/main_test.c:17 (test_flail_intentional_panic)
        """)
