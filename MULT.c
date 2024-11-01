#include "Instruction.h"
//joe hauser
void mult_reg_assm(void) {
	if (strcmp(OP_CODE, "MULT") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}


	setBits_num(31, 0, 6);
	setBits_str(5, "011000");
	setBits_num(15, 0, 10);
	setBits_num(25, PARAM1.value, 5);
	setBits_num(20, PARAM2.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("MULT");

	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);

	state = COMPLETE_DECODE;
}


