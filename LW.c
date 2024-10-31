#include "Instruction.h"

// Sierra Jackson
void lw_immd_assm(void) {
	if (strcmp(OP_CODE, "LW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
	}

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
	}

	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// set opcode
	setBits_str(31, "100011");

	// set Rs
	setBits_num(25, PARAM1.value, 5);

	// offset
	setBits_num(15, PARAM2.value, 16);

	// set Rt
	setBits_num(20, PARAM3.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void lw_immd_bin(void) {
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

	setOp("LW");

	setParam(1, REGISTER, Rs); //first source register operand
	setParam(2, IMMEDIATE, offset);
	setParam(3, REGISTER, Rt); //second source register operand

	state = COMPLETE_DECODE;

}