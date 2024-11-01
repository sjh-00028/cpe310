#include "Instruction.h"

/*
 * Author: Sierra Jackson
 */
void div_reg_assm(void) {
	if (strcmp(OP_CODE, "DIV") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check parameter types
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// check parameter values
	// rs
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// rt
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// set opcode
	setBits_num(31, 0, 6);
	// set funct
	setBits_str(5, "011010");
	// rs
	setBits_num(25, PARAM1.value, 5);
	// rt
	setBits_num(20, PARAM2.value, 5);
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("DIV");

	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);

	state = COMPLETE_DECODE;
}


