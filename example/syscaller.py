import ctypes
import sys
import os

SYS_IS_SESSION_CREATE = 326


def is_session_create():
    libc = ctypes.CDLL(None)
    syscall = libc.syscall
    syscall.restype = ctypes.c_int
    syscall.argtypes = ctypes.c_long, ctypes.c_char_p

    ipport = ctypes.c_char_p("rdma://1,10.0.0.4:9400")

    return syscall(SYS_IS_SESSION_CREATE, ipport)


def main():
    if len(sys.argv) == 1:
        calc_percentage()
    elif len(sys.argv) > 1:
        if sys.argv[1] == 'conn':
            is_session_create()
