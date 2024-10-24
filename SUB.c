/*
* Written by Simon Hale
*/

#include "Instruction.h"

void sub_reg_assm(void) {
	if (strcmp(OP_CODE, "SUB") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	setBits_num(31, 0, 6);
	setBits_num(5, 34, 6);
	setBits_num(15, PARAM1.value, 5);
	setBits_num(25, PARAM2.value, 5);
	setBits_num(20, PARAM3.value, 5);
	state = COMPLETE_ENCODE;
}

void sub_reg_bin(void) {
	if (checkBits(31, "000000") != 0 && checkBits(5, "100010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("SUB");
	setParam(1, REGISTER, Rd);
	setParam(2, REGISTER, Rs);
	setParam(3, REGISTER, Rt);
	state = COMPLETE_DECODE;
}


