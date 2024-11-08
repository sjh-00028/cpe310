#include "Instruction.h"

// Sierra Jackson
void lui_immd_assm(void) {
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check types of parameters
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// check values of parameters
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// set opcode
	setBits_str(31,"001111");
	// set rt
	setBits_num(20, PARAM1.value, 5);
	// set immediate
	setBits_num(15, PARAM2.value, 16);
	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	if (checkBits(31, "001111") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	setOp("LUI");

	setParam(1, REGISTER, Rt); //destination
	setParam(2, IMMEDIATE, imm16); //second source register operand

	state = COMPLETE_DECODE;
}



