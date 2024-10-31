#include "Instruction.h"

// working without offsets
void sw_immd_assm(void) {
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_PARAM;
	}
	// set opcode
	setBits_str(31, "101011");

	// set Rs
	setBits_num(25, PARAM1.value, 5);

	// set Rt
	setBits_num(20, PARAM3.value, 5);

	setBits_num(15, PARAM2.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("SW");

	setParam(1, REGISTER, Rt); //first source register operand
	setParam(2, IMMEDIATE, getBits(15, 16)); 
	setParam(3, REGISTER, Rs);
	state = COMPLETE_DECODE;

}