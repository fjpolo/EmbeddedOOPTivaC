# QUTEST test script corresponding to the test_Sprintf.c test fixture.
# see https://www.state-machine.com/qtools/qutest.html
#
# This example corresponds to SprintfTest.c from Chapter 2 "Test-Driving
# Tools and Conventions" of the book: "Test-Driven Development for Embedded
# Systems" by James W. Grenning

test("No format operations")
glb_filter(GRP_UA)
current_obj(OBJ_AP, "format")
poke(0, 1, bytearray("Hello World!\0", "ascii"))
command(0)
expect("0000000001 SPRINTF_CALL 12 Hello World!")
expect("0000000002 Trg-Done QS_RX_COMMAND")

test("Insert decimal", NORESET)
current_obj(OBJ_AP, "format")
poke(0, 1, bytearray("dec=%d\0", "ascii"))
command(0, 1234)
expect("0000000001 SPRINTF_CALL 8 dec=1234")
expect("0000000002 Trg-Done QS_RX_COMMAND")

test("Insert decimal and string", NORESET)
current_obj(OBJ_AP, "format")
poke(0, 1, bytearray("dec=%d, str=%s\0", "ascii"))
current_obj(OBJ_AP,"string")
poke(0, 1, bytearray("Hello\0", "ascii"))
current_obj(OBJ_AP, "output")
fill(0, 1, 100, 0xAA)
command(0, 4321)
expect("0000000001 SPRINTF_CALL 19 dec=4321, str=Hello")
expect("0000000002 Trg-Done QS_RX_COMMAND")

test("Overflow underflow", NORESET)
current_obj(OBJ_AP, "output")
peek(26, 1, 4)
expect("@timestamp Trg-Peek Offs=26,Size=1,Num=4,Data=<6F,00,AA,AA>")
peek(0, 1, 10)
expect("@timestamp Trg-Peek Offs=0,Size=1,Num=10,Data=<AA,AA,AA,AA,AA,AA,AA,AA,*")

