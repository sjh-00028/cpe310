#include "Instruction.h"

void mfhi_reg_assm(void) {
	if (strcmp(OP_CODE, "MFHI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Set the opcode
	setBits_num(31, 0, 6);

	// Set the funct
	setBits_str(5, "010000");

	// set Rd
	setBits_num(15, PARAM1.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mfhi_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "010001") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rd = getBits(15, 5);

	setOp("MFHI");

	setParam(1, REGISTER, Rd);

	state = COMPLETE_DECODE;
}


