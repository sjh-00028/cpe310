#include "Instruction.h"

void beq_immd_assm(void) {
	if (strcmp(OP_CODE, "BEQ") != 0) {
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
	if (PARAM3.type != IMMEDIATE) {
		state = MISSING_PARAM;
		return;
	}
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	// Set the opcode
setBits_str(31, "000100");

	// set Rs
	setBits_num(25, PARAM1.value, 5);

	// set Rt
	setBits_num(20, PARAM2.value, 5);

	setBits_num(15, PARAM3.value, 16);
	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void beq_immd_bin(void) {
	if (checkBits(31, "000100") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instuciton values
	*/

	setOp("BEQ");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, IMMEDIATE, imm16); //second source register operand


	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}



