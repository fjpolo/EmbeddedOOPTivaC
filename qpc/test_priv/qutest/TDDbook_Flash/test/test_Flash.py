# QUTEST test script corresponding to the test_Flash.c test fixture.
# see https://www.state-machine.com/qtools/html
#
# This example corresponds to FlashTest.cpp test from Chapter 10 "The Mock
# Object" of the book: "Test-Driven Development for Embedded Systems" by
# James W. Grenning

# Flash address and data used in this test group
address = 0x1000
data    = 0xBEEF

# constants from "Flash.h"
FLASH_SUCCESS               = 0
FLASH_VPP_ERROR             = 1
FLASH_PROGRAM_ERROR         = 2
FLASH_PROTECTED_BLOCK_ERROR = 3
FLASH_UNKNOWN_PROGRAM_ERROR = 4
FLASH_READ_BACK_ERROR       = 5
FLASH_TIMEOUT_ERROR         = 6

# constants from "m28w160ect.h"
CommandRegister         = 0x0
StatusRegister          = 0x0

ProgramCommand          = 0x40
Reset                   = 0xFF

ReadyBit                = 1<<7
EraseSuspendBit         = 1<<6
EraseErrorBit           = 1<<5
ProgramErrorBit         = 1<<4
VppErrorBit             = 1<<3
ProgramSuspendBit       = 1<<2
BlockProtectionErrorBit = 1<<1
ReservedBit             = 1<<0


def on_setup():
    command("FAKE_MICROTIME_INIT", 0, 1)
    expect("@timestamp FAKE_MICROTIME_INIT")
    expect("@timestamp Trg-Done QS_RX_COMMAND")


test("Write success ready immediately")
probe("IO_Read", ReadyBit)
probe("IO_Read", data)
command("FLASH_WRITE", address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=128")
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit, StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(data))
expect("@timestamp IO_CALL IO_Read %d %d" %(data, address))
expect("@timestamp FLASH_WRITE %d" %(FLASH_SUCCESS))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write success not immediately ready", NORESET)
probe("IO_Read", 0)
probe("IO_Read", 0)
probe("IO_Read", 0)
probe("IO_Read", ReadyBit)
probe("IO_Read", data)
command("FLASH_WRITE", address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=0")
expect("@timestamp IO_CALL IO_Read 0 %d" %(StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=0")
expect("@timestamp IO_CALL IO_Read 0 %d" %(StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=0")
expect("@timestamp IO_CALL IO_Read 0 %d" %(StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=128")
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit, StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(data))
expect("@timestamp IO_CALL IO_Read %d %d" %(data, address))
expect("@timestamp FLASH_WRITE %d" %(FLASH_SUCCESS))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Vpp Error", NORESET)
probe("IO_Read",ReadyBit | VppErrorBit)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(ReadyBit | VppErrorBit))
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit | VppErrorBit, StatusRegister))
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, Reset))
expect("@timestamp FLASH_WRITE %d" %(FLASH_VPP_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Program Error", NORESET)
probe("IO_Read",ReadyBit|ProgramErrorBit)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(ReadyBit | ProgramErrorBit))
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit | ProgramErrorBit, StatusRegister))
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, Reset))
expect("@timestamp FLASH_WRITE %d" %(FLASH_PROGRAM_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Protected-Block Error", NORESET)
probe("IO_Read",ReadyBit|BlockProtectionErrorBit)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(ReadyBit | BlockProtectionErrorBit))
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit | BlockProtectionErrorBit, StatusRegister))
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, Reset))
expect("@timestamp FLASH_WRITE %d" %(FLASH_PROTECTED_BLOCK_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Unknown Program Error", NORESET)
probe("IO_Read",ReadyBit|EraseSuspendBit|EraseErrorBit|ProgramSuspendBit|ReservedBit)
command("FLASH_WRITE", address, data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(ReadyBit | EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit))
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit | EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit, StatusRegister))
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, Reset))
expect("@timestamp FLASH_WRITE %d" %(FLASH_UNKNOWN_PROGRAM_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Read-Back Error", NORESET)
probe("IO_Read",ReadyBit)
probe("IO_Read",data-1)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(ReadyBit))
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit, StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(data-1))
expect("@timestamp IO_CALL IO_Read %d %d" %(data-1, address))
expect("@timestamp FLASH_WRITE %d" %(FLASH_READ_BACK_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write sucess Ignores Other Bits Until Ready", NORESET)
probe("IO_Read", ~ReadyBit&0xFFFF)
probe("IO_Read", ReadyBit)
probe("IO_Read", data)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(~ReadyBit & 0xFFFF))
expect("@timestamp IO_CALL IO_Read %d %d" %(~ReadyBit & 0xFFFF, StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(ReadyBit))
expect("@timestamp IO_CALL IO_Read %d %d" %(ReadyBit, StatusRegister))
expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(data))
expect("@timestamp IO_CALL IO_Read %d %d" %(data, address))
expect("@timestamp FLASH_WRITE %d" %(FLASH_SUCCESS))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Timeout", NORESET)
command("FAKE_MICROTIME_INIT",0,500)
expect("@timestamp FAKE_MICROTIME_INIT")
expect("@timestamp Trg-Done QS_RX_COMMAND")
for i in range(10):
    probe("IO_Read",~ReadyBit&0xFFFF)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
for i in range(10):
    expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(~ReadyBit & 0xFFFF))
    expect("@timestamp IO_CALL IO_Read %d %d" %(~ReadyBit & 0xFFFF, StatusRegister))
expect("@timestamp FLASH_WRITE %d" %(FLASH_TIMEOUT_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")

test("Write fails Timeout at End-Of-Time", NORESET)
command("FAKE_MICROTIME_INIT",0xFFFFFFFF,500)
expect("@timestamp FAKE_MICROTIME_INIT")
expect("@timestamp Trg-Done QS_RX_COMMAND")
for i in range(10):
    probe("IO_Read",~ReadyBit&0xFFFF)
command("FLASH_WRITE",address,data)
expect("@timestamp IO_CALL IO_Write %d %d" %(CommandRegister, ProgramCommand))
expect("@timestamp IO_CALL IO_Write %d %d" %(address, data))
for i in range(10):
    expect("@timestamp TstProbe Fun=IO_Read,Data=%d" %(~ReadyBit & 0xFFFF))
    expect("@timestamp IO_CALL IO_Read %d %d" %(~ReadyBit & 0xFFFF, StatusRegister))
expect("@timestamp FLASH_WRITE %d" %(FLASH_TIMEOUT_ERROR))
expect("@timestamp Trg-Done QS_RX_COMMAND")
