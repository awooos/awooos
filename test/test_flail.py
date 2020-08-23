"""
Tests for the flail-test executable.
"""

from pathlib import Path
import subprocess
from textwrap import dedent


def test_flail():
    path = Path(__file__).resolve().parent / 'flail-test'
    result = subprocess.run(str(path), capture_output=True, text=True, check=True)

    assert result.stdout == dedent("""\
        !!! Kernel panic !!!

        Flail test executable

        This kernel panic is intentional.

        Stack dump:

        <insert stack dump here>


        Kernel panic: This kernel panic is intentional.
         src/main_test.c:17 (test_flail_intentional_panic)
    """)
