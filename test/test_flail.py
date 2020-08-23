"""
Tests for the flail-test executable.
"""

from pathlib import Path
import subprocess


def test_flail():
    """Basic integration test for Flail."""
    path = Path(__file__).resolve().parent / 'flail-test'
    result = subprocess.run(str(path), capture_output=True, text=True, check=True)

    lines = result.stdout.splitlines()

    assert lines.pop(0) == "!!! Kernel panic !!!"
    assert lines.pop(0) == ""
    assert lines.pop(0) == "Flail test executable"
    assert lines.pop(0) == ""
    assert lines.pop(0) == "This kernel panic is intentional."
    assert lines.pop(0) == ""
    assert lines.pop(0) == "Stack dump:"
    assert lines.pop(0) == ""
    assert lines.pop(0).endswith(": 0x1")
    assert lines.pop(0).endswith(": 0x2")
    assert lines.pop(0).endswith(": 0xbadf00d")
    assert lines.pop(0).endswith(": 0xdeadbeef")
    assert lines.pop(0).endswith(": 0x9999999999999999")
    assert lines.pop(0).endswith(": 0x0")
    assert lines.pop(0) == ""
    assert lines.pop(0) == ""
    assert lines.pop(0) == "Kernel panic: This kernel panic is intentional."
    assert lines.pop(0) == " src/main_test.c:17 (test_flail_intentional_panic)"
